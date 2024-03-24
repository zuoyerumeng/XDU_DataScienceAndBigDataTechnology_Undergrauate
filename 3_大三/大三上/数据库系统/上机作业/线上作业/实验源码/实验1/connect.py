import pymysql
connection = pymysql.connect(host='Host',
port=Port,
user='zuoyerumeng',
passwd='#jiang666',
db='Database')
try:
    with connection.cursor() as cursor:
    # 以查询courses表为例
    sql = "SELECT * FROM `courses`"
    cursor.execute(sql)
    for result in cursor:
        # 输出查询结果
        print(result)
finally:
    connection.close()