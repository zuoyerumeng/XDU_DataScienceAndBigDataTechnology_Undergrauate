public class WordCountDriver{



    public static void main(String[] args) throws Exception {
        //创建配置文件
        Configuration conf = new Configuration();
        // 1：创建job对象
        Job job = Job.getInstance(conf);
        //2：指定job所在的jar包。
        job.setJarByClass(WordCountDriver.class);
        //3：指定 mapper 类和 reducer 类
        job.setMapperClass(WordCountMapper.class);
        job.setReducerClass(WordCountReducer.class);
        //4.1：指定 MapTask 的输出key-value类型（可以省略）
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(LongWritable.class);
        //4.2：指定 ReduceTask 的输出key-value类型
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(LongWritable.class);
        //5：设置输入输出路径
        Path inPath=new Path("/root/wordcount.txt");
        Path outpath=new Path("/root/output1");
        FileSystem fs=FileSystem.get(conf);
        //判断输出路径是否存在，存在将删除目录
        if(fs.exists(outpath)){
            fs.delete(outpath,true);
        }
        FileInputFormat.setInputPaths(job,inPath);
        FileOutputFormat.setOutputPath(job, outpath);
        //6：代码提交yarn集群，等待运行完反馈信息，客户端退出
        boolean bl = job.waitForCompletion(true);
        System.exit(bl?0:1);
    }
}
