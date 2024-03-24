// void tablejoin(tableNode* tablenode, char* row, int index, storageNode* sp);
// void open(storageNode* sp, char* tablename, int rowlength);
// void rnd_init(storageNode* sp);
// bool isEOF(storageNode* sp);
// char* rnd_next(storageNode* sp);
// void write_row(storageNode* sp, char* row);

	/*if (tablenode->next->next != NULL)
	{
		tablejoin(tablenode->next, row, index, sp);
		tablenode->next->next;
		// firstnode->next = generateTempTable(firstnode->next, n + 1);
	}*/

#include"QueryProcessor.h"
#include "StorageClass.h"		//不能在queryprocessor.h头文件中引用 WHY?

//using namespace std;

char* usedatabase;			/*当前使用的数据库*/

void setUseDB(char* dbname) {
//	if (usedatabase != NULL) delete[] usedatabase;
	usedatabase = new char[strlen(dbname)+1];
	strcpy_s(usedatabase, strlen(dbname)+1, dbname);
}

char* dbnameADDtablename(char* dbname, char* tablename) {
	char* fileend = stringcat("\\", tablename);
	char* filename = stringcat(dbname, fileend);
	return filename;
}

bool isMateDataTable(char* tablename) {
	if (strcmp("system_db", tablename) == 0 
		|| strcmp("system_table", tablename) == 0
		|| strcmp("system_col", tablename) == 0 )
		return true;
	else
		return false;
}

void setColInColData(coldatanode* coldatanode, colNode* colnode) {
	coldatanode->colname = colnode->colname;
	coldatanode->tablename = colnode->tablename;
	coldatanode->coltype = colnode->coltype;
	coldatanode->size = colnode->size;
	coldatanode->data = new char[colnode->size];
	coldatanode->data[0] = '\0';
}

void setDataInColData(coldatanode* coldatanode, char* data) {
	memcpy_s(coldatanode->data, coldatanode->size, data, coldatanode->size);
}

void colListToDataArray(colNodeList* list, coldatanode* dataarray) {
	colNode* node = list->head;
	for (int i = 0; i < list->num; i++) {
		setColInColData(dataarray+i, node);		/*对数组中第i+1个元素处理*/
		node = node->next;
	}
}

void colDataToRow(coldatanode* dataarray, int arraynum, char* row) {
	int offset = 0;
	for (int i = 0; i < arraynum; i++) {
		memcpy_s(row+offset, dataarray[i].size, dataarray[i].data, dataarray[i].size);
		offset += dataarray[i].size;
	}
}

void rowToColData(char* row, coldatanode* dataarray, int arraynum) {
	int i;
	int offset = 0;		/*字节数组偏移量*/
	for (i = 0; i < arraynum; i++) {
		setDataInColData(dataarray + i, row + offset);
		offset += dataarray[i].size;
	}
}

bool isExistDB(char* dbname) {
	bool isExist;
	dbNodeList* list = selectDB(dbname);
	
	if (list->num == 0) 
		isExist = false;
	else 
		isExist = true;

	deleteDBNodeList(list);
	return isExist;
}

void createDB(char* dbname) {}

void dropDB(char* dbname) {}

void useDB(char* dbname) {
	if (!isExistDB(dbname)) {
		printf("%s is not Exist", dbname);
		return;
	}

	setUseDB(dbname);
	printf("use %s", dbname);
	return;
}

void showDB() {
	dbNodeList* dbnodelist = selectDB(NULL);
	/* 输出数据库名称 */
	printf("dbname：\n");

	dbNode* dbnode = dbnodelist->head;
	for (int i = 0; i < dbnodelist->num; i++) {
		printf("%s\n", dbnode->dbname);
		dbnode = dbnode->next;
	}
	printf("total %d databases", dbnodelist->num);
	return;
}

void showTable() {
	tableNodeList* tablelist = selectDBTable(NULL, usedatabase);

	/* 输出列名 */
	printf("tablename\tcolnum\trowlength\n");

	tableNode* tablenode = tablelist->head;
	for (int i = 0; i < tablelist->num; i++) {
		printf("%s\t%d\t%d\n", tablenode->tablename, tablenode->colnum, tablenode->rowlength);
		tablenode = tablenode->next;
	}
	printf("total %d tables", tablelist->num);
	return;
}

bool isExistTable(char* tablename) {
	bool isExist;
	tableNodeList* list = selectDBTable(tablename,usedatabase);

	if (list->num == 0) 
		isExist = false;
	else 
		isExist = true;

	deleteTableNodeList(list);

	return isExist;
}

void createTable(struct createTablesql* createTablesql) {}

void dropTable(char* tablename) {}

void insert(struct insertsql* insertsql) {}

void tablejoin(tableNode* tablenode, char* row, int index, storageNode* sp) {
	//sp：储存temp临时表信息的结构体
	//tablenode：第一个表的表元信息节点
	if (index == 0)
	{

		tableNode* firstnode = tablenode;
		//第一个用户数据表的表名（带有相对路径）
		char* firstfilename = dbnameADDtablename(usedatabase, firstnode->tablename);
		storageNode* firstsp = createStorageNode();		//储存第一个用户数据表信息的结构体
		open(firstsp, firstfilename, firstnode->rowlength);
		rnd_init(firstsp);


		//对第一个用户数据表中的每一个元组，都打开第二个表读取所有元组并拼接，将结果写入temp临时表
		while (!isEOF(firstsp)) {
			char* first_row = rnd_next(firstsp);		//读取第一个表的一个元组
			if (first_row == NULL) //读取到被删除数据，返回空值
				continue;

			//将第一张表一行数据放入row数组中
			memcpy_s(row, firstnode->rowlength, first_row, firstnode->rowlength); 
			int firstindex = index + firstnode->rowlength;

			//第二个表的表元信息节点
			tableNode* secondnode = firstnode->next;
			char* secondfilename = dbnameADDtablename(usedatabase, secondnode -> tablename);
			storageNode* secondsp = createStorageNode();
			open(secondsp, secondfilename, secondnode->rowlength);
			rnd_init(secondsp);
			//遍历第二个表所有的元组，逐个与第一个表中选中的元组拼接
			while (!isEOF(secondsp)) {
				char* second_row = rnd_next(secondsp);
				if (second_row == NULL)
					continue;
				memcpy_s(row+firstindex, secondnode->rowlength, second_row, secondnode -> rowlength);
				int secondindex = firstindex + secondnode->rowlength;
				//将第二张表的一行数据添加到row数组末尾
				if (secondnode->next != NULL)
					tablejoin(secondnode, row, secondindex, sp);
				else
					write_row(sp, row);
			} 
			close(secondsp);
			deleteStorageNode(secondsp);
		}
		/* 清除缓存 */
		close(firstsp);
		deleteStorageNode(firstsp);
		return;
	}
	tableNode* secondnode = tablenode->next;
	char* secondfilename = dbnameADDtablename(usedatabase, secondnode->tablename);
	storageNode* secondsp = createStorageNode();
	open(secondsp, secondfilename, secondnode->rowlength);
	rnd_init(secondsp);
	//遍历第二个表所有的元组，逐个与第一个表中选中的元组拼接
	while (!isEOF(secondsp)) {
		char* second_row = rnd_next(secondsp);
		if (second_row == NULL)
			continue;
		memcpy_s(row + index, secondnode->rowlength, second_row, secondnode->rowlength);
		int secondindex = index + secondnode->rowlength;
		//将第二张表的一行数据添加到row数组末尾
		if (secondnode->next != NULL)
			tablejoin(secondnode, row, secondindex, sp);
		else
			write_row(sp, row);
	}
	close(secondsp);
	deleteStorageNode(secondsp);
}

tableNode* generateTempTable(tableNodeList* tablelist) {
	/* 创建临时表 */
	char tablename[] = "temp";
	char* filename = dbnameADDtablename(usedatabase, tablename);
	if (!create(filename)) {
		printf("create temp error");
		return NULL;
	}

	/* 初始化临时表tablenode内列数量和行长度 */
	tableNode* tablenode = createTableNode();		/*创建临时表节点*/
	setTableNode(tablenode, tablename, 0, 0);		
	tableNode* node = tablelist->head;
	for (int i = 0; i < tablelist->num; i++) {		/*计算临时表的列数、行长度*/
		tablenode->colnum += node->colnum;
		tablenode->rowlength += node->rowlength;
		node = node->next;
	}

	/* 创建用于记录笛卡尔积中元组的字节数组row,并打开临时表 */
	char* row = new char[tablenode->rowlength];
	storageNode* sp = createStorageNode();
	open(sp, filename, tablenode->rowlength);

	/* 调用笛卡尔积函数 */
	tablejoin(tablelist->head, row, 0, sp);

	/* 清除缓存 */
	close(sp);
	deleteStorageNode(sp);


	return tablenode;
}

bool deleteTempTable() {
	char tablename[] = "temp";
	char* filename = dbnameADDtablename(usedatabase, tablename);
	if (!drop(filename)) {
		printf("drop temp error");
		return false;
	}
	return true;
}

int selectColname(char* tablename, char* colname, coldatanode* datanodearray, int arraynum) {
	int i;			/*datanodearray数组的下标*/
	int num = 0;	/*命中的datanodearray数组元素的个数*/
	int index;		/*列名对应的datanodearray数组元素的下标*/
	for (i = 0; i < arraynum; i++) {
		if (tablename == NULL || strcmp(tablename,datanodearray[i].tablename)==0) {
			if (strcmp(colname, datanodearray[i].colname) == 0) {
				num++;
				index = i;
			}
		}
	}

	switch (num) {
		case 0: printf("can't find col"); return -1;
		case 1: return index;
		default: printf("have more cols"); return -1;
	}
}

bool conditionLinkData(struct condition* conditions, coldatanode* datanodearray, int arraynum) {return false;}

bool checkconditions(struct condition* conditions) { return false; }

void showcolname(char* tablename, char* colname) {
	if (tablename != NULL) 
		printf("%s.", tablename);
	printf("%s\t", colname);
}


bool dealcalcondition(struct condition* condition) { return false; }

bool dealstringcondition(struct condition* condition) { return false; }

bool dealconditions(struct condition* conditions) { return false; }

void showcoldata(coldatanode* dataarray, int* showorder, int shownum) {
	int i;
	for (i = 0; i < shownum; i++) {
		int j = showorder[i];
		/* 输出值为空时输出NULL */
		if (dataarray[j].data[0] == '\0') {
			printf("NULL\t");
			continue;
		}
		switch (dataarray[j].coltype) {
			case 1: printf("%d\t", *(int*)dataarray[j].data); break;
			case 2: printf("%s\t", dataarray[j].data); break;
		}
	}
	printf("\n");
}

void select(struct selectsql* selectsql) {
	/* 判断是否use database，存在bug，如果查询system_db表，不需要use database，但实现有点麻烦，故未修改 */
	if (usedatabase == NULL ) {
		printf("error: not use database");
		return;
	}

	/* 读取查询表元数据，并判断数据表是否存在 */
	struct tablecol* tables = selectsql->tables;
	struct tableNodeList* tablelist = new struct tableNodeList;		/*表元信息链表*/

	/*得到所有待查询表的表元信息*/
	while (tables != NULL)
	{
		struct tableNodeList* list;
		
		/*判断待查询的表是否为系统表*/
		if (isMateDataTable(tables->tablename))		/* 元数据表的元数据信息不需要加usedatabasename */
			list = selectDBTable(tables->tablename, NULL);
		else 
			list = selectDBTable(tables->tablename, usedatabase);
		if (list->num == 0) {
			printf("table not exist");
			return;
		}
		appendTableNodeList(tablelist, list);	/*将表元信息储存在tablelist链表中*/
		tables = tables->next;
		delete list;
	}
	
	/* 判断数据表数量，大于一张表时对多张表进行笛卡尔积 */
	tableNode* tablenode;		/*查询处理中用到的表*/
	if (tablelist->num > 1) {
		if (tablelist->num > 2) {
			printf("error: the number of tables is not more than 2");
			return;
		}
		tablenode = generateTempTable(tablelist);
	}
	else 
		tablenode = tablelist->head;
	
	/* 读取列元数据 */
	struct colNodeList* collist = new struct colNodeList;	/*collist：储存元数据管理器返回的列元信息*/
	struct tableNode* node = tablelist->head;
	for (int i = 0; i < tablelist->num; i++) {
		struct colNodeList* list;
		/* 元数据表的元数据信息不需要加usedatabasename */
		if (isMateDataTable(node->tablename)) 
			list = selectTableCol(node->tablename, NULL);
		else 
			list = selectTableCol(node->tablename, usedatabase);
		appendColNodeList(collist, list);		/*将查询到的列元信息储存到链表中*/
		delete list;
		node = node->next;
	}
	if (collist->num != tablenode->colnum) {
		printf("get metadata error");
		return;
	}

	/* 创建列数据数组，并绑定列元数据结构 */
	coldatanode* dataarray = new coldatanode[collist->num];	/*dataarray：列数据数组*/
	colListToDataArray(collist, dataarray);

	/*条件查询*/
	if (selectsql->whereconf != NULL) {
		/* 存在where条件时，将where内tablecol与coldatanode绑定，同时判断tablecol是否不存在或者重复 */
		if (!conditionLinkData(selectsql->whereconf, dataarray, collist->num)) 
			return;
		/* 判断where条件内比较类型是否相同 */
		if (!checkconditions(selectsql->whereconf))
			return;
	}

	/* 判断查询结果数据列名称不存在或者有重复，输出并记录其顺序 */

	/*在第一行输出列名，并通过遍历链表获得showorder数组*/
	int* showorder = new int[collist->num * 2];  /*showorder,记录指定输出的列及其顺序，大小默认为coldatanode数量的2倍*/
	int shownum = 0;
	if (selectsql->tablecolconf->isALL == 0) {	/*选择全部列，并按顺序输出全部列*/
		for (int i = 0; i < collist->num; i++) {
			if (tablelist->num == 1)	/*单表查询*/
				showcolname(NULL, dataarray[i].colname);	
			else						/*多表查询*/
				showcolname(dataarray[i].tablename, dataarray[i].colname);	/*输出列名时要家上数据库名称*/
			showorder[i] = i;
			shownum++;
		}
	}
	else {	/*选择部分列，即条件查询*/
		struct tablecol* cols = selectsql->tablecolconf->tablecols;		/*cols：select命令要求输出的列*/
		int index;		/*储存列在dataarray列数据数组中的下标*/
		while(cols != NULL) {
			index = selectColname(cols->tablename, cols->colname, dataarray, collist->num);
			if (index == -1) 
				return;
			showcolname(cols->tablename, cols->colname);	/*输出列名*/
			showorder[shownum] = index;			/*将列的下标存入showorder数组*/
			shownum++;
			cols = cols->next;
		}
	}

	printf("\n");

	
	char* filename;
	/* 数据库元数据表在根目录下，不需要在表名前加usedatabase名称 */
	if (strcmp("system_db", tablenode->tablename) == 0) 
		filename = tablenode->tablename;
	else 
		filename = dbnameADDtablename(usedatabase, tablenode->tablename);
	
	/* 打开表 */
	storageNode* sp = createStorageNode();
	if (!open(sp, filename, tablenode->rowlength)) {
		printf("open table error");
		return;
	}
	rnd_init(sp);
	int num = 0;

	/*遍历数据表*/
	while (!isEOF(sp)) {
		/* 读取一行数据，将存入dataarray数组中 */
		char* row = rnd_next(sp);
		if (row == NULL) 
			continue;
		rowToColData(row, dataarray,collist->num);

	    /* 执行where条件判断，where为真时，将指定列输出 */
		if (selectsql->whereconf == NULL || dealconditions(selectsql->whereconf)) {
			showcoldata(dataarray, showorder, shownum);
			num++;
		}
	}
	printf("Total row: %d", num);

	/* 关闭表 */
	close(sp);
	deleteStorageNode(sp);

	/* 临时表则删除表 */
	if (tablelist->num > 1) deleteTempTable();

	/* 清除缓存 */
	delete[] dataarray;
	delete[] showorder;
	deleteColNodeList(collist);
	deleteTableNodeList(tablelist);

	return;
}


void updatesetconf(struct setconf* setconfs) {}

void update(struct updatesql* updatesql) {}

void deletetable(struct deletesql* deletesql) {}



