import subprocess
import time
import json
from monitor_panel import show_stats

def get_stats():
    try:
        output = subprocess.check_output(["../../bin/monitor.exe"]).decode()
        return json.loads(output)
    except Exception as e:
        return {"cpu": 0, "ram": 0, "error": str(e)}

if __name__ == "__main__":
    while True:
        stats = get_stats()
        show_stats(stats)
        time.sleep(1)
