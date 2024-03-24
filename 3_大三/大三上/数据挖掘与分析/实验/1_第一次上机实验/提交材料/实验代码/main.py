import scanpy as sc
import numpy as np
import scipy.stats as st
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import cosine_similarity

# 数据读取（得到Anndata对象）
adata=sc.read_10x_mtx(r"..\..\数据集\Breast_Cancer_3p_filtered_feature_bc_matrix\filtered_feature_bc_matrix", cache=True) 


# 设置相关参数
sc.settings.verbosity = 3 # errors为0,warnings为1,info为2,hints为3
sc.logging.print_header() # 可能影响数值结果的版本
sc.settings.set_figure_params(dpi=80, facecolor='white') # 设置绘图的分辨率/大小和颜色


# 数据预处理
adata.var_names_make_unique() # 去重
    # 基本过滤  
sc.pp.filter_cells(adata, min_genes=3000) # 去除表达基因3000以下的细胞
sc.pp.filter_genes(adata, min_cells=50) # 去除在50个细胞以下表达的基因
    # 去除表达过多线粒体基因和总计数过多的细胞
# sc.pl.scatter(adata, x='total_counts', y='pct_counts_mt')
# sc.pl.scatter(adata, x='total_counts', y='n_genes_by_counts')
    # 通过对对象进行切片来进行过滤
# adata = adata[adata.obs.n_genes_by_counts < 2500, :]
# adata = adata[adata.obs.pct_counts_mt < 5, :]
sc.pp.normalize_total(adata, target_sum=1e4) # 将总计数归一化（库大小校正）为每单元格 10,000 个读取，以便计数在单元格之间具有可比性
sc.pp.log1p(adata) # 对数据进行对数化
# sc.pp.scale(adata, max_value=10) # 将每个基因缩放到单位方差。剪辑值超过标准偏差 10
# adata = adata[:, adata.var.highly_variable] # 实际进行过滤


# 一些基本量的计算
mtx=adata.X
cnt_barcodes=len(mtx.indptr)-1 # 计算细胞总数      
cnt_genes=max(mtx.indices)+1 # 计算基因总数
cnt_expression=len(mtx.data) # 计算基因表达总次数(不包括表达量为0的情况)
print("细胞、基因总数分别为{0}、{1}".format(cnt_barcodes,cnt_genes))    


# 1、数据的汇总统计分析
print("\n","1、数据的汇总统计分析")    
    # 计算单个细胞（样本）表达的取值范围
        # 计算单个细胞中所有基因表达量总和，并获取最大值和最小值
min_expression=sum(mtx.data)
max_expression=0
expression_barcodes=np.zeros(cnt_barcodes)
for i in range(cnt_barcodes-1):
    sum_expression=sum(mtx.data[mtx.indptr[i]:mtx.indptr[i+1]])
    expression_barcodes[i]=sum_expression
    if sum_expression>max_expression: max_expression=sum_expression
    if sum_expression<min_expression and sum_expression>0: min_expression=sum_expression
print("单个细胞基因表达的取值范围（除去未表达的情况，即表达量为0之外）为{0}~{1}".format(min_expression,max_expression))

    # 统计分析“0”的出现次数
cnt_0=np.int64(cnt_barcodes*cnt_genes-cnt_expression) 
print("\n","Breast_Cancer_3p_filtered_feature_bc_matrix数据集中0出现了{0}次，出现比例为{1:.3f}%；平均每个细胞、每个基因中分别出现了{2:.3f}、{3:.3f}次".format(cnt_0,100*cnt_0/(cnt_barcodes*cnt_genes),cnt_0/cnt_barcodes,cnt_0/cnt_genes,'.3f'))

    # 均值、方差等的统计分析结果
print("\n","均值、方差等的统计分析结果：")
        # 分别计算每个基因在所有细胞中表达量的总和
expression_genes=np.zeros(cnt_genes)
for i,j in enumerate(mtx.indices):
    expression_genes[j]+=mtx.data[i]
        # 计算两个数据集中细胞基因表达量的统计量（均值、方差、最值、极差、中位数、四分位数、总和等）
print("基因表达量的总和为{0:.3f}".format(np.sum(mtx.data),'.3f'))
print("以细胞为主体的基因表达量相关统计量如下：")
print("    均值为{0:.3f}".format(np.mean(expression_barcodes),'.3f'))
print("    方差为{0:.3f}".format(np.var(expression_barcodes),'.3f'))
print("    最大值、最小值分别为{0:.3f}、{1:.3f}，极差为{2:.3f}".format(np.max(expression_barcodes),np.min(expression_barcodes),np.max(expression_barcodes)-np.min(expression_barcodes),'.3f'))
print("    中位数为{0:.3f}".format(np.median(expression_barcodes),'.3f'))
print("    上、下四分位数分别为{0:.3f}、{1:.3f}".format(np.percentile(expression_barcodes,75),np.percentile(expression_barcodes,25),'.3f'))
print("    偏度为{0:.3f}".format(st.skew(expression_barcodes),'.3f'))
print("    峰度为{0:.3f}".format(st.kurtosis(expression_barcodes),'.3f'))
print("以基因为主体的基因表达量相关统计量如下：")
print("    均值为{0:.3f}".format(np.mean(expression_genes),'.3f'))
print("    方差为{0:.3f}".format(np.var(expression_genes),'.3f'))
print("    最大值、最小值分别为{0:.3f}、{1:.3f}，极差为{2:.3f}".format(np.max(expression_genes),np.min(expression_genes),np.max(expression_genes)-np.min(expression_genes),'.3f'))
print("    中位数为{0:.3f}".format(np.median(expression_genes),'.3f'))
print("    上、下四分位数分别为{0:.3f}、{1:.3f}".format(np.percentile(expression_genes,75),np.percentile(expression_genes,25),'.3f'))
print("    偏度为{0:.3f}".format(st.skew(expression_genes),'.3f'))
print("    峰度为{0:.3f}".format(st.kurtosis(expression_genes),'.3f'))


# 2、 数据的可视化
    # 绘制1*2的小提琴组图
plt.rcParams['font.sans-serif']=['SimHei'] # 使图表内的中文能够正常显示
plt.rcParams.update({"font.size":20}) # 设置字体大小
plt.figure(figsize=(16,9))
ax=plt.subplot(1,2,1) 
violin_barcodes=sns.violinplot(data=expression_barcodes) # 绘制小提琴图
ax.set_title("按细胞")
ax.set_ylabel("基因表达量")
ax=plt.subplot(1,2,2)
violin_genes=sns.violinplot(data=expression_genes)
ax.set_title("按基因")
plt.suptitle("Breast_Cancer_3p_filtered_feature_bc_matrix数据集")
plt.savefig(r"..\实验报告\LaTeX源代码\figures\fig2.png")
plt.savefig(r"..\实验结果\统计分析的可视化结果（小提琴图）.png")
plt.show()
plt.close()

    # 计算并可视化高度可变基因的表达情况
sc.pp.highly_variable_genes(adata, min_mean=0.0125, max_mean=3, min_disp=0.5)
sc.pl.highly_variable_genes(adata, show=False)
plt.savefig(r"..\实验结果\高度可变基因表达情况散点图.png")
plt.savefig(r"..\实验报告\LaTeX源代码\figures\fig3.png")
plt.show()
plt.close()

    # 计算并可视化所有细胞中表达占比最高的基因
sc.pl.highest_expr_genes(adata, n_top=20, show=False)
plt.savefig(r"..\实验结果\所有细胞中表达占比最高的基因.png")
plt.savefig(r"..\实验报告\LaTeX源代码\figures\fig4.png")
plt.show()
plt.close()


# 3、构建共表达网络并可视化
    # 构建行为细胞，列为基因，值为基因表达量的二维矩阵
expression_mtx=np.zeros((cnt_barcodes,cnt_genes))
for i in range(len(mtx.indptr)-1):
    for j in range(mtx.indptr[i],mtx.indptr[i+1]):
        expression_mtx[i][mtx.indices[j]]+=mtx.data[j]

    # 计算所有基因对两两之间的皮尔森相关系数
expression_df=pd.DataFrame(expression_mtx)
pearson_genes=expression_df.corr(method="pearson")
pearson_genes.to_excel(r"..\实验结果\基因对之间的皮尔森相关系数.xlsx")
        # 将结果存为由（节点，节点，权重）格式构成的网络表格
network_genes_np=np.array([[]])
for i in range(cnt_genes):
    for j in range(i):
            # 按皮尔森相关系数大于0.9的条件，过滤出相似性较强的的节点之间的边
        if pearson_genes[i][j]>0.9: 
            np.append(network_genes_np,[i,j,pearson_genes[i][j]])
network_genes_df=pd.DataFrame(network_genes_np)
network_genes_df.to_excel(r"..\..\网络Excel\基因对之间的皮尔森相关系数.xlsx")

    # 用余弦相似度计算细胞之间的相似性 
cosine_similarity_np=cosine_similarity(expression_mtx)
cosine_similarity_pd=pd.DataFrame(cosine_similarity_np) # 把npy格式文件转换为DataFrame数据类型
cosine_similarity_pd.to_excel(r"..\实验结果\细胞之间的相似度.xlsx") # 将结果存为Excel表格
        # 将结果存为由（节点，节点，权重）格式构成的网络表格
network_barcodes_np=np.array([[]])
for i in range(cnt_barcodes):
    for j in range(i):
            # 按余弦相似度大于0.95的条件，过滤出相似性较强的的节点之间的边
        if cosine_similarity_np[i][j]>0.95: 
            np.append(network_barcodes_np,[i,j,cosine_similarity_np[i][j]])
network_barcodes_df=pd.DataFrame(network_barcodes_np)
network_barcodes_df.to_excel("..\..\网络Excel\细胞之间的相似度.xlsx")