# Simple Dockerfile for the Toy-Generator service (Python-based)

FROM python:3.10-slim

WORKDIR /app

# Copy only the toy-generator service to keep image small
COPY services/toy-generator/ /app

# Install Python dependencies if provided
RUN if [ -f requirements.txt ]; then pip install --no-cache-dir -r requirements.txt; fi

# Default command — adjust depending on which script you want to run
CMD ["python", "src/tools/watermarker.py"]
