import json
import matplotlib.pyplot as plt

def plot_trajectory(json_file="planning/trajectory.json"):
    with open(json_file, "r") as f:
        trajectory = json.load(f)

    x_vals = [pt["x"] for pt in trajectory]
    y_vals = [pt["y"] for pt in trajectory]
    headings = [pt["heading"] for pt in trajectory]

    plt.figure(figsize=(10, 6))
    plt.plot(x_vals, y_vals, label="Trajectory", color="blue", linewidth=2)
    plt.scatter(x_vals[0], y_vals[0], color="green", label="Start", s=50)
    plt.scatter(x_vals[-1], y_vals[-1], color="red", label="End", s=50)

    plt.title("Generated Trajectory")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend()
    plt.axis("equal")
    plt.tight_layout()
    plt.savefig("planning/trajectory_plot.png")
    plt.show()

if __name__ == "__main__":
    plot_trajectory()
