"""
DATABASE MIGRATION CLI TOOL (UNFINISHED)
"""


import typer
from typing import Annotated, List, Tuple
from rich.console import Console
from rich.table import Table
from enum import Enum

console = Console()

main_app = typer.Typer(help = "Production level Database migration tool")
db = typer.Typer(help = "migrate/status")

main_app.add_typer(db, name="db")

def callback(size : int):
    if not (100 <= size <= 50000):
        raise typer.BadParameter("Bad batch size.")

class FormatEnum(str, Enum):
    CSV = "csv"
    JSON = "json"
    PARQUET = "parquet"
    SQL = "sql"

@main_app.callback()
def global_options(
    verbose: Annotated[
        bool,
        typer.Option("--verbose", "-v", help = "Makes the CLI more verbose")
    ] = False
):
    if verbose:
        console.print("[bold yellow]Tool in verbose mode[/bold yellow]")


@db.command("migrate")
def migration(
    source: Annotated[
        str,
        typer.Argument(help="Source database string (e.g., postgres_analytics)")
    ],

    target: Annotated[
        str,
        typer.Argument(help="Target database string (e.g., postgres_analytics)")
    ],
    
    api_key: Annotated[
        str,
        typer.Option(envvar = "DATASHIFT_KEY", prompt = "Enter API Key: ", hide_input = True)
    ],

    format : FormatEnum = FormatEnum.SQL,

    tables: Annotated[
        List[str],
        typer.Option("--table", "-t", help = "Table flags")
    ] = None,
    
    host_port: Annotated[
        Tuple[str, int],
        typer.Option("--server", help = "Accept a host IP/domain and port number pair")
    ] = ("localhost", 5432),

    batch_size: Annotated[
        int,
        typer.Option("--batch-size", callback = callback)
    ] = 1000
    
):

    if target == "prod" and len(api_key) < 8:
        console.print("[bold red] ERROR! [/bold red]")
        raise typer.Exit(1)
    
    console.print(f"[bold yellow]Source[/bold yellow]:[bold green] {source}[/bold green]")
    console.print(f"[bold yellow]Target[/bold yellow]:[bold green] {target}[/bold green]")
    console.print(f"[bold yellow]API Key: {api_key}[/bold yellow]")
    console.print(f"[bold yellow]Format[/bold yellow]:[bold green] {format}[/bold green]")
    console.print(f"[bold yellow]Tables[/bold yellow]:[bold green] {tables}[/bold green]")
    console.print(f"[bold yellow]Host Port[/bold yellow]:[bold green] {host_port}[/bold green]")
    console.print(f"[bold yellow]Batch Size[/bold yellow]:[bold green] {batch_size}[/bold green]")



@db.command("status")
def status():
    table = Table(title="Connection Status")
    table.add_column("Database", header_style="cyan")
    table.add_column("Region", header_style="magenta")
    table.add_column("Status", header_style="yellow")
    table.add_column("Latency", header_style="purple")

    table.add_row("PostgreSQL", "India", "Connected", "~25ms")
    table.add_row("ChromaDB", "USA", "Connected", "~27ms")
    table.add_row("PineCone", "Germany", "Connecting", "...")

    console.print(table)


if __name__ == "__main__":
    main_app()
   


