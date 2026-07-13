# covscript-sqlite

SQLite3 database bindings for Covariant Script.

## Dependencies

- [Covariant Script](https://github.com/covscript/covscript)
- SQLite3 (bundled as amalgamation)

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## API

### sqlite::database

| Method | Description |
|--------|-------------|
| `open(path)` | Open or create a SQLite database file |
| `close()` | Close the database connection |
| `exec(sql)` | Execute a SQL statement |

### sqlite::statement

| Method | Description |
|--------|-------------|
| `prepare(db, sql)` | Prepare a SQL statement |
| `bind(index, value)` | Bind a value to a parameter |
| `step()` | Execute one step |
| `reset()` | Reset the prepared statement |
| `finalize()` | Finalize the statement |

## License

Apache License 2.0 — see [LICENSE](./LICENSE)
