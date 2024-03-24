/*
 * 数据库
 */
#pragma once
#include <map>
#include <string>
#include <memory>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <exception>


class Database {
  friend std::ostream& operator << (std::ostream &os, const Database &item);

public:
  Database() = default;

  // 加入名为 name 的数据表
  void insert(const std::string &name, const std::vector<std::string> &title,
      const std::vector<ElementType> &types) {
    if (data.find(name) != data.end())
      throw std::runtime_error("Add existent datatable: " + name + ".");
    data[name] = std::make_shared<DataTable>(title, types);
  }

  // 删除名为 name 的数据表
  void erase(const std::string &name) {
    auto ite = data.find(name);
    if (ite == data.end())
      throw std::runtime_error("Delete nonexistent datatable: " + name + ".");
    data.erase(ite);
  }

  // 返回指向名为 name 的数据表的 shared_ptr
  std::shared_ptr<DataTable> find(const std::string &name) {
    auto ite = data.find(name);
    if (ite == data.end())
      throw std::runtime_error("Use nonexistent datatable: " + name + ".");
    return ite->second;
  }

  // 给 database 的 save() 用的
  void save(std::ofstream &fo) {
    fo << data.size() << '\n';
    for (auto &v: data) {
      fo << "datatable" << ' ' << v.first << '\n';
      v.second->save(fo);
    }
  }

private:
  std::map<std::string, std::shared_ptr<DataTable>> data;
};

std::ostream& operator << (std::ostream &os, const Database &item) {
  for (auto &v: item.data)
    os << "Data table " + v.first + ":\n" << *v.second;
  return os;
}

class Data {
  friend std::ostream& operator << (std::ostream &os, const Data &item);

public:
  Data() = default;

  // 返回当前使用的 database, 未设置时为空值
  std::shared_ptr<Database>& cur() {
    return current;
  }

  // 加入名为 name 的数据库
  void insert(const std::string &name) {
    if (dbs.find(name) != dbs.end())
      throw std::runtime_error("Add existent database: " + name + ".");
    dbs[name] = std::make_shared<Database>();
  }

  // 选择数据库
  std::shared_ptr<Database>& use(const std::string &name) {
    auto ite = dbs.find(name);
    if (ite == dbs.end())
      throw std::runtime_error("Use nonexistent database: " + name + ".");
    return current = ite->second;
  }

  // 删除数据库
  void erase(const std::string &name) {
    auto ite = dbs.find(name);
    if (ite == dbs.end())
      throw std::runtime_error("Delete nonexistent database: " + name + ".");
    dbs.erase(ite);
  }

  // 返回指向名为 name 的数据库的 shared_ptr
  std::shared_ptr<Database> find(const std::string &name) {
    auto ite = dbs.find(name);
    if (ite == dbs.end())
      throw std::runtime_error("Use nonexistent database: " + name + ".");
    return ite->second;
  }

  // 保存为 filename
  void save(const std::string &filename = "databases.data") {
    std::ofstream fo(filename);
    if (!fo) return;
    for (auto &v: dbs) {
      fo << "database" << ' ' << v.first << '\n';
      v.second->save(fo);
    }
  }

  // 从 filename 读取数据, 不检查文件内容是否合法
  void load(const std::string &filename = "databases.data") {
    std::ifstream fi(filename);
    if (!fi) return;
    std::string type, name, value;
    int dtn, colm, rows;
    while (fi >> type >> name) { // type == "database"
      insert(name), use(name);
      fi >> dtn;
      for (int i = 0; i < dtn; ++i) {
        fi >> type >> name; // type == "datatable"
        // 读取表头
        fi >> colm;
        std::vector<std::string> titles(colm);
        for (int j = 0; j < colm; ++j) fi >> titles[j];
        std::vector<ElementType> types(colm);
        for (int x, j = 0; j < colm; ++j)
          fi >> x, types[j] = itoEt(x);
        current->insert(name, titles, types);
        // 读取数据
        auto pdt = current->find(name);
        fi >> rows;
        std::vector<std::string> values(colm);
        for (int k = 0; k < rows; ++k) {
          for (int j = 0; j < colm; ++j) fi >> values[j];
          pdt->insert(titles, values);
        }
      }
    }
  }

private:
  std::shared_ptr<Database> current;
  std::map<std::string, std::shared_ptr<Database>> dbs;
};

std::ostream& operator << (std::ostream& os, const Data &item) {
  for (auto &v: item.dbs)
    os << "Database " << v.first << ":\n" << *v.second << '\n';
  return os;












  #include "datatable.cpp"
