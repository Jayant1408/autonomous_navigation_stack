from ultralytics import YOLO
import cv2
import json

def detect_and_save_obstacles(image_path, output_json = "planning/obstacles.json"):
    model = YOLO("yolov8n.pt")

    results  = model(image_path)[0]
    annotated = results.plot()
    cv2.imwrite("perception/object_detection/output.jpg", annotated)
    obstacles = []
    for box in results.boxes:
        cls = int(box.cls[0])
        if cls in [0,1]:
            x1, y1, x2, y2 = map(float, box.xyxy[0])
            x_center = (x1 + x2) / 2
            y_center = (y1 + y2) / 2
            radius = max(x2 - x1, y2 - y1) / 2
            obstacles.append({
                "x": round(x_center,2),
                "y": round(y_center,2),
                "radius": round(radius,2)
            })

    with open(output_json, "w") as f:
        json.dump(obstacles, f, indent = 2)

    print(f"[INFO] Wrote {len(obstacles)} obstacles to {output_json}")


if __name__ == "__main__":
    # detect_and_save_obstacles("Lane_detection_test.jpg")
    detect_and_save_obstacles("test.jpg")
