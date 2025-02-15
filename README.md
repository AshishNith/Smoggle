# **Smoggle - Smart Glasses for the Visually Impaired** 👓🎙️  

![Smoggle Banner](https://via.placeholder.com/1000x400?text=Smoggle+-+Smart+Glasses+for+Blind+People)  

**Smoggle** is an AI-powered smart glasses system designed to help visually impaired individuals navigate their surroundings independently. It uses an **ESP32-CAM** to capture images, sends them to an **LLM (GPT-4 Vision API) for analysis**, and provides real-time **in-ear audio feedback** using **text-to-speech (TTS)**.  

---

## 🌟 **Features**
✅ **AI-Powered Object Recognition** – Identifies objects, signs, and obstacles in the user's environment.  
✅ **Text-to-Speech (TTS)** – Converts AI-generated descriptions into speech for real-time guidance.  
✅ **Lightweight & Portable** – Designed to fit into a compact smart glasses frame.  
✅ **Wi-Fi Connectivity** – Sends images to a remote server for processing.  
✅ **Easy to Use** – Works automatically or via a button press.  

---

## 🚀 **How It Works**
1️⃣ The **ESP32-CAM** captures an image of the environment.  
2️⃣ The image is sent to a **Flask server**, which processes it using **GPT-4 Vision API**.  
3️⃣ The AI analyzes the image and generates a description.  
4️⃣ The description is converted into speech using **pyttsx3** (offline TTS).  
5️⃣ The spoken response is played through an **earpiece or speaker**.  

---

## 🛠 **Technologies Used**
- **ESP32-CAM** – For image capture  
- **Python (Flask)** – Backend server  
- **OpenAI GPT-4 Vision API** – For image analysis  
- **OpenCV & Ultralytics YOLO** – For object detection  
- **Numpy** – For image processing  
- **pyttsx3** – For offline Text-to-Speech (TTS)  
- **Arduino IDE** – For ESP32-CAM programming  

---

## 📂 **Project Structure**
```
smoggle/
│── esp32_code/        # ESP32-CAM firmware
│   ├── smoggle.ino    
│── server/            # Python backend
│   ├── app.py       
│── requirements.txt   # Python dependencies
│── README.md          # Documentation
```

---

## 🔧 **Installation & Setup**
### **1️⃣ Setting Up ESP32-CAM**
1. Install **Arduino IDE** and add the **ESP32 board package**.  
2. Connect ESP32-CAM to your PC via **FTDI adapter**.  
3. Upload the `smoggle.ino` code from `esp32_code/`.  

### **2️⃣ Installing Python Dependencies**
Before running the server, install the required Python libraries:  

#### **Installing dependencies from requirements.txt**
Run the following command in your terminal or command prompt:  
```bash
pip install -r requirements.txt
```

#### **Or install manually:**
```bash
pip install flask openai numpy opencv-python pyttsx3 ultralytics
```

### **3️⃣ Setting Up the Server**
1. Replace `"your_openai_api_key"` in `app.py` with your OpenAI API key.  
2. Start the server:  
   ```bash
   python server/app.py
   ```

---

## 🎯 **How to Use**
1️⃣ **Power On** the ESP32-CAM module.  
2️⃣ **Connect to Wi-Fi** (configured in `smoggle.ino`).  
3️⃣ The glasses will automatically **capture images** and analyze the surroundings.  
4️⃣ The system **speaks out** detected objects and text to assist the user.  

---

## 🎯 **Future Improvements**
🔹 Optimize AI processing for faster response times.  
🔹 Implement **voice commands** for additional interaction.  
🔹 Enhance **battery efficiency** for prolonged usage.  
🔹 Add **edge AI** to reduce dependency on the internet.  

---

## 💡 **Contributing**
We welcome contributions! Feel free to **fork the repository**, submit **pull requests**, or **open issues**.  

---

## 📜 **License**
This project is **open-source** and feel free to contribute.  

---

## ✨ **Team & Credits**
Developed by **Shirshak Mondal and Ashish Ranjan** and contributors 🚀  
Special thanks to **OpenAI**, **Ultralytics**, **OpenCV**, and the **ESP32 community** for their amazing tools!  

---

**Smoggle – Empowering the Visually Impaired with AI** 🌍👓✨