import scanpy as sc
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import metrics
from scipy import stats
from munkres import Munkres


# 数据读取
df=pd.DataFrame(pd.read_csv(r"..\数据集\Zeisel_df.csv"))
adata=sc.AnnData(X=df) # 将CSV文件生成的DataFrame对象转换为AnnData对象	


# 设置相关参数
sc.settings.verbosity=3 # errors为0,warnings为1,info为2,hints为3
sc.logging.print_header() # 可能影响数值结果的版本
sc.settings.set_figure_params(dpi=80, facecolor='white') # 设置绘图的分辨率/大小和颜色
adata.var_names_make_unique() # 基因去重


# 1、特征选择和降维
	# 通过方差筛选从所有基因中选择最具信息量的基因
# sc.pp.scale(adata, max_value=10) # 将每个基因缩放到单位方差。剪辑值超过标准偏差 10
# adata = adata[:, adata.var.highly_variable] # 实际进行过滤
	# 使用主成分分析（PCA）降维方法将高维数据映射到较低维空间
sc.tl.pca(adata, svd_solver='arpack')
sc.pl.pca(adata, show=False) # 根据PCA坐标绘制散点图
plt.savefig(r"PCA散点图.png")
sc.pl.pca_variance_ratio(adata, log=True, show=False) # 计算单个PC对数据总方差的贡献
plt.savefig(r"单个PC对数据总方差的贡献.png")
plt.show()
plt.close()
adata.write("PCA.h5ad") # 保存结果


# 2、聚类算法应用（使用leiden算法进行聚类分析）
sc.pp.neighbors(adata, n_neighbors=10, n_pcs=40) # 计算邻域图
	# 将图形嵌入二维
sc.tl.umap(adata) # 使用UMAP
# sc.pl.umap(adata, use_raw=False, show=False) # 归一化、对数化、校正
# plt.savefig(r"..\实验报告\LaTeX源代码\figures\fig4.png")
# plt.savefig(r"UMAP二维嵌入图.png")
	# 正式聚类分析
sc.tl.leiden(adata) # 聚类分析
sc.pl.umap(adata, show=False) # 可视化（未标记细胞类型）
plt.savefig(r"leiden聚类邻域图.png")
plt.show()
plt.close()
adata.write(r"聚类得分矩阵（未标记细胞类型）.h5ad") # 保存结果
labels_pred=np.array((sc.read_h5ad(r"聚类得分矩阵（未标记细胞类型）.h5ad")).obs)
(pd.DataFrame(labels_pred)).to_csv(r"聚类标签.csv",index=False)
labels_pred=(np.transpose(labels_pred))[0] # 获取聚类标签
labels_pred=labels_pred.astype(np.int64)


# 3、聚类结果评估和可视化
	# 计算内部、外部聚类指标
    	# 在聚类分析结果标签与真实标签之间建立映射
def KM(L1:list, L2:list)->list: # KM（Kuhn-Munkres）匈牙利算法
	Label1=np.unique(L1) # 去除重复的元素，由小大大排列
	nClass1=len(Label1) # 标签的大小
	Label2=np.unique(L2)       
	nClass2=len(Label2)
	nClass=np.maximum(nClass1,nClass2)
	G=np.zeros((nClass,nClass))
	for i in range(nClass1):
		ind_cla1=L1==Label1[i]
		ind_cla1=ind_cla1.astype(float)
		for j in range(nClass2):
			ind_cla2=L2==Label2[j]
			ind_cla2=ind_cla2.astype(float)
			G[i,j]=np.sum(ind_cla2 * ind_cla1)
	m=Munkres()
	index=m.compute(-G.T)
	index=np.array(index)
	c=index[:,1]
	newL2=np.zeros(L2.shape)
	for i in range(nClass2):
		newL2[L2==Label2[i]]=Label1[c[i]]
	return newL2

    	# 调用函数
labels_true=(np.transpose(np.genfromtxt(r"..\数据集\sclabel.csv")))[1:] # 获取真实标签
labels_true=labels_true.astype(np.int64)
# for i in range(6):
#     labels_true[-i-1]=12+i
# labels_pred=KM(labels_true,labels_pred)

def purity_score(y_true:list, y_pred:list)->float: # 定义purity（纯度）计算函数
    y_voted_labels=np.zeros(y_true.shape)
    labels=np.unique(y_true)
    ordered_labels=np.arange(labels.shape[0])
    for k in range(labels.shape[0]):
        y_true[y_true==labels[k]]=ordered_labels[k]
    labels=np.unique(y_true)
    bins=np.concatenate((labels, [np.max(labels)+1]), axis=0)
    for cluster in np.unique(y_pred):
        hist, _=np.histogram(y_true[y_pred==cluster], bins=bins)
        winner=np.argmax(hist)
        y_voted_labels[y_pred==cluster]=winner
    return metrics.accuracy_score(y_true, y_voted_labels)

print("\n聚类指标计算结果:")
print("	内部指标：")
print("		轮廓系数（SC，Silhouette Coefficient Index）为{0:.3f}".format(1+metrics.silhouette_score(X=df, labels=labels_pred)))
print("		DBi指数（Davies-Bouldin Index，戴维森堡丁指数）为{0:.3f}".format(metrics.davies_bouldin_score(X=df, labels=labels_pred)))
print("		CH（Calinski-Harabaz指数，又称方差比准则）为{0:.3f}".format(metrics.calinski_harabasz_score(X=df, labels=labels_pred)))
print("	外部指标：")
print("		RI（兰德系数）为{0:.3f}".format(metrics.rand_score(labels_true=labels_true, labels_pred=labels_pred)),)
print("		ARI（调整兰德系数）为{0:.3f}".format(1-metrics.adjusted_rand_score(labels_true=labels_true, labels_pred=labels_pred)))
print("		MI（互信息分数）为{0:.3f}".format(1-metrics.adjusted_rand_score(labels_true=labels_true, labels_pred=labels_pred)))
print("		AMI（调整互信息分数）为{0:.3f}".format(metrics.adjusted_mutual_info_score(labels_true=labels_true, labels_pred=labels_pred)))
print("		NMI（标准化互信息分数）为{0:.3f}".format(metrics.normalized_mutual_info_score(labels_true=labels_true, labels_pred=labels_pred)))
print("		FMI（Fowlkes–Mallows指数）为{0:.3f}".format(metrics.fowlkes_mallows_score(labels_true=labels_true, labels_pred=labels_pred)))
# print("		总熵为{0:.3f}".format(stats.entropy(pk=list(labels_true), qk=list(labels_pred))))
print("		Purity（纯度）为{0:.3f}%".format(100*purity_score(y_true=labels_true, y_pred=labels_pred)))
print("		Precision（精确度）为{:.3f}%".format(100*(1-metrics.precision_score(y_true=labels_true, y_pred=labels_pred, average='macro'))))
print("		ACC（准确度）为{0:.3f}%".format(100*(1-metrics.accuracy_score(y_true=labels_true, y_pred=labels_pred))))
print("		Recall（召回率）为{0:.3f}%".format(100*(1-metrics.recall_score(y_true=labels_true, y_pred=labels_pred, average='macro'))))
print("		F1 score（F度量）为{0:.3f}".format(1-metrics.f1_score(y_true=labels_true, y_pred=labels_pred, average='macro')))
print("		Jaccard系数为{0:.3f}".format(1-metrics.jaccard_score(y_true=labels_true, y_pred=labels_pred, average='macro')))

	# 使用二维降维方法UMAP对聚类结果进行可视化展示
		# 计算每类细胞的标记基因
sc.settings.verbosity=2  # 减少冗余度
sc.tl.rank_genes_groups(adata, 'leiden', method='logreg') # 用logreg多变量评估差分测试包计算
sc.pl.rank_genes_groups(adata, n_genes=25, sharey=False, show=False)
plt.savefig(r"每个簇中高度差异基因排名.png")
plt.show()
plt.close()
marker_genes=["Ccl27a_loc1","Ryr2","Wfs1","Ttr","Reln","2610001J05Rik","Mog","Gpr17","Vip","Itm2a","Metrn","Itgb4","Itm2a","Aqp4","Nxph3","Tyrobp"]
pd.DataFrame(adata.uns['rank_genes_groups']['names']).head(5) # 在数据帧中显示每个聚类排名最高的 10 个基因
#     	# 获取包含分数和组的表格
# result=adata.uns['rank_genes_groups']
# groups=result['names'].dtype.names
# pd.DataFrame(
#     {group + '_' + key[:1]: result[key][group]
#     for group in groups for key in ['names', 'pvals']}).head(5)
# sc.pl.rank_genes_groups_violin(adata, groups='0', n_genes=8) # 使用计算出的差分表达式重新加载对象（即通过与其他组的比较来重新加载 DE）
		# 可视化展示
new_cluster_names=["Ccl27a_loc1","Ryr2","Wfs1","Ttr","Reln","2610001J05Rik","Mog","Gpr17","Vip","Itm2a_1","Metrn","Itgb4","Itm2a_2","Aqp4","Nxph3","Tyrobp","Lyz2"] # 提取聚类名称
adata.rename_categories('leiden', new_cluster_names) # 重命名聚类名称
sc.pl.umap(adata=adata, color='leiden', add_outline=True, legend_loc='on data', legend_fontsize=12, legend_fontoutline=2,frameon=False, title='', palette='Set1', show=False) # 可视化（标记细胞类型）
plt.savefig(r"聚类结果散点图（标记细胞类型）.png")
plt.show()
plt.close()
sc.pl.dotplot(adata, marker_genes, groupby='leiden', show=False); # 绘制标记基因气泡图
plt.savefig(r"标记基因气泡图.png")
plt.show()
plt.close()
sc.pl.stacked_violin(adata, marker_genes, groupby='leiden', rotation=90, show=False); # 绘制标记基因小提琴图 
plt.savefig(r"标记基因小提琴图.png")
plt.show()
plt.close()
adata.write(r"聚类得分矩阵（标记细胞类型）.h5ad") # 保存结果
