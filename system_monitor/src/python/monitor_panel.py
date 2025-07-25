from rich.console import Console
from rich.panel import Panel

def show_stats(stats):
    console = Console()
    panel_text = f"[bold cyan]CPU:[/bold cyan] {stats['cpu']:.2f}%\n"
    panel_text += f"[bold magenta]RAM:[/bold magenta] {stats['ram']:.2f}%"
    console.clear()
    console.print(Panel(panel_text, title="System Monitor", subtitle="Real-time Stats", expand=False))
