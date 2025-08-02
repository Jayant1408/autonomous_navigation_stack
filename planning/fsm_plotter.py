import pandas as pd
import matplotlib.pyplot as plt
import json

def plot_fsm_with_obstacles():
    log = pd.read_csv("planning/fsm_log.csv")

    # Force numeric types to prevent plotting issues
    log["x"] = pd.to_numeric(log["x"], errors="coerce")
    log["y"] = pd.to_numeric(log["y"], errors="coerce")

    with open("planning/obstacles.json", "r") as f:
        obstacles = json.load(f)

    plt.figure(figsize=(10, 6))
    plt.title("FSM Planner Trajectory with Obstacles")
    plt.xlabel("X")
    plt.ylabel("Y")

    # Plot trajectory segments with debug prints
    for i in range(len(log) - 1):
        x0, y0 = float(log.iloc[i]["x"]), float(log.iloc[i]["y"])
        x1, y1 = float(log.iloc[i + 1]["x"]), float(log.iloc[i + 1]["y"])
        state = log.iloc[i]["state"]
        color = "blue" if state == "GO_STRAIGHT" else "orange"
        print(f"Segment {i}: ({x0:.2f},{y0:.2f}) → ({x1:.2f},{y1:.2f}) [{state}]")
        plt.plot([x0, x1], [y0, y1], color=color, linewidth=2)

    # Plot FSM state transitions
    for state in ["GO_STRAIGHT", "STOP"]:
        state_rows = log[log["state"] == state]
        color = "green" if state == "GO_STRAIGHT" else "red"
        plt.scatter(state_rows["x"], state_rows["y"], color=color, s=40, label=state)

    # Plot obstacles
    for obs in obstacles:
        circle = plt.Circle((obs["x"], obs["y"]), obs["radius"], color="red", fill=False, linewidth=1.5)
        plt.gca().add_patch(circle)

    plt.legend()
    plt.grid(True)
    plt.axis("equal")
    plt.tight_layout()
    plt.savefig("planning/fsm_plot.png")
    plt.show()

if __name__ == "__main__":
    plot_fsm_with_obstacles()
