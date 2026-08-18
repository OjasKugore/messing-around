# DataShift CLI

A production-style database migration and sync CLI tool built with [Typer](https://typer.tiangolo.com/) and [Rich](https://rich.readthedocs.io/).

## Commands

### `clitool db migrate`

Migrate data between two databases.

```bash
uv run --package clitool clitool db migrate <source> <target> [OPTIONS]
```

| Flag | Type | Description |
|------|------|-------------|
| `source` | str | Source database connection string |
| `target` | str | Target database connection string |
| `--format` | enum | Export format: `csv`, `json`, `parquet`, `sql` (default: `sql`) |
| `--table / -t` | str (repeatable) | Filter specific tables |
| `--server` | (str, int) | Host and port pair (default: `localhost 5432`) |
| `--batch-size` | int | Batch size between 100–50,000 (default: 1000) |
| `--api-key` | str | DataShift API key (reads `DATASHIFT_KEY` env var; prompts if absent) |

### `clitool db status`

Show a Rich table of dummy database connection statuses.

```bash
uv run --package clitool clitool db status
```

## Examples

```bash
# Check connection status
uv run --package clitool clitool db status

# Migrate with specific tables and custom server
uv run --package clitool clitool db migrate db_a prod \
  -t users -t orders \
  --server 10.0.0.1 5432 \
  --format csv

# Migrate with a large batch size
uv run --package clitool clitool db migrate db_a db_b --batch-size 5000
```
