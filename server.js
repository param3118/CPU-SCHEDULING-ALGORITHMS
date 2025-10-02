const express = require('express');
const { exec } = require('child_process');
const cors = require('cors');

const app = express();
const port = 3000;

app.use(cors());  // enable all CORS
app.use(express.json());
// app.use(express.static('.')); // serve frontend files
app.use(express.static('public')); // put index.html inside "public" folder


// Debug middleware
app.use((req, res, next) => {
  console.log(`❓ Unknown request: ${req.method} ${req.url}`);
  next();
});

app.post('/run-cpp', (req, res) => {
  const { algo, inputs } = req.body;
  console.log("📥 Received request:", req.body);

  if (!algo || !inputs) {
    return res.status(400).json({ error: "Missing algo or inputs" });
  }

  const cppFile = `${algo}.cpp`;
  const inputStr = inputs.join(" ");
  console.log(`⚡ Running: g++ ${cppFile} -o ${algo} && echo "${inputStr}" | ./${algo}`);

  exec(`g++ "${cppFile}" -o "${algo}" && echo "${inputStr}" | ./"${algo}"`,
    (error, stdout, stderr) => {
      if (error) {
        console.error("❌ C++ Error:", stderr);
        return res.status(500).json({ error: stderr });
      }
      console.log("📤 Raw C++ output:", stdout);

      try {
        const result = JSON.parse(stdout);
        console.log("✅ Parsed JSON:", result);
        res.json(result);
      } catch (e) {
        console.error("⚠️ JSON parse failed. Sending raw output.");
        res.json({ error: "Invalid C++ output", raw: stdout });
      }
    });
});

app.listen(port, () => {
  console.log(`🚀 Server running on http://localhost:${port}`);
});
