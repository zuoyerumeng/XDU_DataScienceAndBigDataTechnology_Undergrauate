-- 创建一个名为test_table的测试表
CREATE TABLE test_table (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR(50) NOT NULL,
  age INT NOT NULL,
  PRIMARY KEY (id)
);

-- 向test_table表中插入3条数据
INSERT INTO test_table (name, age) VALUES
  ('John', 25),
  ('Mary', 30),
  ('Bob', 35);

  SELECT * FROM test_table;

UPDATE test_table
SET name = 'Johnny', age = 26
WHERE id = 1;