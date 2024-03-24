#include <cstdio>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "include/database.hpp"

using VecStr = std::vector<std::string>;

const char *WILDCARD = "<all>";

// 验证命令 cmd 格式是否符合 verified
bool verifyCommand(const VecStr &cmd, const VecStr &verified, size_t start = 0) {
  if (cmd.size() < verified.size() + start)
    return false;
  for (size_t i = 0; i < verified.size(); ++i)
    if (verified[i] != WILDCARD && cmd[start + i] != verified[i])
      return false;
  return true;
}

// 数据 dbs 中的数据库管理
bool databaseManage(const VecStr &cmd, Data &dbs) {
  // 数据库创建
  if (verifyCommand(cmd, { "create", "database", WILDCARD, ";" })) {
    const std::string &name = cmd[2];
    dbs.insert(name);
    return true;
  }

  // 数据库删除
  if (verifyCommand(cmd, { "drop", "database", WILDCARD, ";" })) {
    const std::string &name = cmd[2];
    dbs.erase(name);
    return true;
  }

  // 数据库选择
  if (verifyCommand(cmd, { "use", WILDCARD, ";" })) {
    const std::string &name = cmd[1];
    dbs.use(name);
    return true;
  }

  // 数据库显示
  if (verifyCommand(cmd, { "info", "database", WILDCARD, ";" })) {
    const std::string &name = cmd[2];
    std::cout << "Database " << name << ":\n" << *dbs.find(name);
    return true;
  }
  // 显示所有数据
  if (verifyCommand(cmd, { "info", ";" })) {
    std::cout << dbs;
    return true;
  }

  return false;
}

// 根据 str 内容判断对应数据类型
ElementType getElementType(const std::string &str) {
  if (str.find("int") != std::string::npos)
    return ElementType::Int;
  if (str.find("float") != std::string::npos)
    return ElementType::Float;
  if (str.find("string") != std::string::npos)
    return ElementType::String;
  return ElementType::None;
}

// 数据库中的数据表管理
bool dataTableManage(const VecStr &cmd, std::shared_ptr<Database> pdb) {
  if (!pdb) return false;

  // 数据表创建
  if (verifyCommand(cmd, { "create", "table", WILDCARD, "(" })) {
    const std::string &tablename = cmd[2];

    VecStr title;
    std::vector<ElementType> types;
    for (size_t i = 4; i + 2 < cmd.size(); i += 3) {
      types.push_back(getElementType(cmd[i]));
      title.push_back(cmd[i + 1]);
      if (cmd[i + 2] == ")") break;
    }
    pdb->insert(tablename, title, types);

    return true;
  }

  // 数据表删除
  if (verifyCommand(cmd, { "drop", "table", WILDCARD, ";" })) {
    const std::string &tablename = cmd[2];
    pdb->erase(tablename);
    return true;
  }

  // 显示表信息
  if (verifyCommand(cmd, { "info", "table", WILDCARD, ";" })) {
    const std::string &tablename = cmd[2];
    std::cout << "Data table " << tablename << ":\n" << *pdb->find(tablename);
    return true;
  }

  return false;
}

// 数据库中的数据表修改
bool dataTableModify(const VecStr &cmd, std::shared_ptr<Database> pdb) {
  if (!pdb) return false;

  // 数据表中插入记录
  if (verifyCommand(cmd, { "insert", "into", WILDCARD, "set" } )) {
    std::string tablename = cmd[2];
    auto pdt = pdb->find(tablename);

    VecStr names, values;
    for (size_t i = 4; i + 2 < cmd.size() && cmd[i + 1] == "="; i += 4) {
      names.push_back(cmd[i]);
      values.push_back(cmd[i + 2]);
    }
    pdt->insert(names, values);
    return true;
  }

  // 数据表内删除记录
  if (verifyCommand(cmd, {
        "delete", "from", WILDCARD, "where", WILDCARD, WILDCARD, WILDCARD
      })) {
    // 删除一定条件下的记录
    std::string tablename = cmd[2], name = cmd[4], sign = cmd[5], value = cmd[6];
    pdb->find(tablename)->erase(name, sign, value);
    return true;
  } else if (cmd.size() == 3 && verifyCommand(cmd, { "delete", "from", WILDCARD, ";" })) {
    // 删除所有记录
    std::string tablename = cmd[2];
    pdb->find(tablename)->clear();
    return true;
  }

  return false;
}

// 数据库中的数据表查询
bool dataTableSearch(const VecStr &cmd, std::shared_ptr<Database> pdb) {
  if (!pdb) return false;

  // 数据表内查询符合条件的记录
  if (verifyCommand(cmd, { "select", WILDCARD })) {
    std::string order;
    bool reversed = false;
    VecStr names, columns, signs, values;
    size_t cur = 1;
    // select [col_name1], [col_name2], ...
    if (!verifyCommand(cmd, { "*" }, cur)) {
      for ( ; cur + 1 < cmd.size(); cur += 2) {
        names.push_back(cmd[cur]);
        if (cmd[cur + 1] == "from") break;
      }
    }
    ++cur;
    // from [table name]
    if (!verifyCommand(cmd, { "from", WILDCARD }, cur))
      return false;
    std::string tablename = cmd[cur + 1];
    auto pdt = pdb->find(tablename);
    cur += 2;
    // where [condition1], [condition2], ...
    if (verifyCommand(cmd, { "where", WILDCARD, WILDCARD, WILDCARD }, cur)) {
      ++cur;
      for ( ; cur + 2 < cmd.size(); cur += 3) {
        if (cmd[cur] == "order") break;
        columns.push_back(cmd[cur]);
        signs.push_back(cmd[cur + 1]);
        values.push_back(cmd[cur + 2]);
      }
    }
    // order by [column name] [asc/desc]
    if (verifyCommand(cmd, { "order", "by", WILDCARD }, cur)) {
      order = cmd[cur + 2];
      if (cur + 3 < cmd.size()) {
        if (cmd[cur + 3] != ";" && cmd[cur + 3] != "asc" && cmd[cur + 3] != "desc")
          return false;
        reversed = (cmd[cur + 3] == "desc");
      }
    }

    if (names.size() > 0) {// 显示给定字段
      if (columns.size() > 0)
        pdt->select(std::cout, names, columns, signs, values, order, reversed);
      else
        pdt->select(std::cout, names, order, reversed);
    } else { // 显示所有字段
      if (columns.size() > 0)
        pdt->select(std::cout, columns, signs, values, order, reversed);
      else
        pdt->select(std::cout, order, reversed);
    }
    return true;
  }
  return false;
}

// 解析输入的指令
void parseCommand(VecStr &cmd) {
  std::string line;
  do {
    std::cout << "> ";
    std::getline(std::cin, line);

    for (size_t i = 0, j = 1; i < line.size(); i = j++) {
      if (std::isspace(line[i])) continue;
      // 对于 '(', ')', ',', ';' 的情况, 单独提取
      auto isSeparator = [](char ch) {
        return ch == '(' || ch == ')' || ch == ',' || ch == ';';
      };
      // 对 condition 中的比较运算, 单独提取
      auto isCondition = [](char ch) {
        return ch == '<' || ch == '>' || ch == '=';
      };
      if (isSeparator(line[i])) {
        j = i + 1;
      } else {
        bool quoteFlag = (line[i] == '\''); // 单引号之间视作整体
        while (j < line.size() && (quoteFlag // 包含所有字符, 直到下一处 '\''
            || (!isspace(line[j]) && !isSeparator(line[j]) // 剔除空格与分隔符
            && isCondition(line[i]) == isCondition(line[j])))) // 比较运算单独处理: 此处运算符可能不是单独一个字符
          quoteFlag ^= (line[j++] == '\'');
      }
      if (line[i] == '\'' && line[j - 1] == '\'') { // 此处将字符串两端 '\'' 去除
        cmd.push_back(line.substr(i + 1, j - i - 2));
      } else {
        cmd.push_back(line.substr(i, j - i));
      }
    }
  } while (cmd.size() > 0 && cmd.back() != ";");

}

int main() {
  Data data;
  data.load();

  while (true) {
    VecStr cmd;
    // 解析输入的指令
    parseCommand(cmd);
    // 退出程序
    if (*cmd.begin() == "exit") break;

    try {
      // 数据库操作
      bool flag = databaseManage(cmd, data);
      // 数据表操作
      auto pdb = data.cur();
      if (pdb) {
        flag |= flag? true: dataTableManage(cmd, pdb);
        flag |= flag? true: (dataTableModify(cmd, pdb) || dataTableSearch(cmd, pdb));
      }
      if (flag) { // 数据记录发生变化, 保存
        data.save();
        // std::cout << data;
      } else {
        std::cout << "Wrong input format." << '\n';
      }
    } catch(std::runtime_error &e) { // 异常处理...
      std::cout << "Invalid command: " << e.what() << '\n';
    }
  }
  return 0;
}