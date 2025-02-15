import cv2
import numpy as np
import pyttsx3
from ultralytics import YOLO

engine = pyttsx3.init()
engine.setProperty('rate', 150)
engine.setProperty('volume', 1.0)

model = YOLO("yolov8n.pt")

cap = cv2.VideoCapture(0)

cv2.namedWindow("Object Detection", cv2.WINDOW_NORMAL)
cv2.resizeWindow("Object Detection", 1580, 720)

last_spoken = None

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    results = model(frame)

    side_panel = np.zeros((frame.shape[0], 300, 3), dtype=np.uint8)

    detected_objects = []
    for result in results:
        for box in result.boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])
            conf = box.conf[0]
            cls = int(box.cls[0])
            label = model.names[cls]

            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(frame, f"{label} ({conf:.2f})", (x1, y1 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

            detected_objects.append(label)

    y_offset = 30
    unique_objects = list(set(detected_objects))

    for obj in unique_objects:
        cv2.putText(side_panel, obj, (10, y_offset), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
        y_offset += 30

    if unique_objects:
        first_object = unique_objects[0]
        if first_object != last_spoken:
            engine.say(first_object)
            engine.runAndWait()
            last_spoken = first_object

    output_frame = np.hstack((frame, side_panel))

    cv2.imshow("Object Detection", output_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()