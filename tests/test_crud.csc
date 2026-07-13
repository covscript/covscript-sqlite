# Basic CRUD test for covscript-sqlite
import sqlite

# Create in-memory database
var db = sqlite.open(":memory:")

# Create table
var stmt = sqlite.prepare(db, "CREATE TABLE test (id INTEGER, name TEXT)")
sqlite.statement.exec(stmt)

# Insert
var insert = sqlite.prepare(db, "INSERT INTO test VALUES (?, ?)")
sqlite.statement.bind_integer(insert, 0, 1)
sqlite.statement.bind_text(insert, 1, "hello")
sqlite.statement.exec(insert)

# Select
var select = sqlite.prepare(db, "SELECT * FROM test WHERE id = ?")
sqlite.statement.bind_integer(select, 0, 1)
sqlite.statement.exec(select)

var col_count = sqlite.statement.column_count(select)
var id = sqlite.statement.column_integer(select, 0)
var name = sqlite.statement.column_text(select, 1)

system.out.println("columns: " + col_count)
system.out.println("id: " + id)
system.out.println("name: " + name)

# Verify
if id != 1 || name != "hello"
    throw "CRUD test FAILED"
end
system.out.println("CRUD test PASSED")
