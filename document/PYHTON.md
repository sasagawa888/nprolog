# Python Library to use TensorFlow
under construction

# Install Tensorflow

```
sudo apt install python3-pip
pip install tensorflow-cpu

```

# Preparation
The Plot library utilizes the C language embedding feature. Therefore, it needs to be compiled first. Please follow the steps below to compile it.

```
make prolog
```

# Usage

```
?- use_module(python).
```

# Example

```
# calc.py test for tensorflow
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
import tensorflow as tf
print(tf.add(1, 2).numpy())
```

```
N-Prolog Ver 4.07
?- use_module(python).
yes
?- send_python('./tests/calc.py',X).
python3 ./tests/calc.py3
X = $3
$ .
yes
?- 
```

# Specification

- `send_python(File,Result)'
Provide a file name to Python 3 and receive the execution result as a string.

# Note
This feature was created for TensorFlow. However, since it's simply instructing Python, I believe it can be applied to other uses as well.

# Idea note

```
exec.py 
?- send_python('exec.py image.jpg', X).

import sys
import tensorflow as tf
from tensorflow.keras.preprocessing import image
import numpy as np

# Get the image file path from command-line arguments
if len(sys.argv) != 2:
    print("Usage: python3 exec.py <image_path>")
    sys.exit(1)

img_path = sys.argv[1]  # Image file path

# Load the MobileNetV2 model pre-trained on ImageNet
model = tf.keras.applications.MobileNetV2(weights='imagenet')

# Load and resize the image to the input size of the model (224x224)
img = image.load_img(img_path, target_size=(224, 224))

# Convert the image to a NumPy array
img_array = image.img_to_array(img)

# Add a batch dimension (the model expects input in batches)
img_array = np.expand_dims(img_array, axis=0)

# Normalize the pixel values to be between 0 and 1
img_array = img_array / 255.0

# Perform inference (make predictions)
predictions = model.predict(img_array)

# Decode the predictions (convert them to human-readable labels)
decoded_predictions = tf.keras.applications.mobilenet_v2.decode_predictions(predictions, top=3)

# Simple conclusion output for Prolog: "cat" or "dog"
for i, (imagenet_id, label, score) in enumerate(decoded_predictions[0]):
    if 'cat' in label.lower():
        print("cat")  # Output "cat" if the result is related to cat
        break
    elif 'dog' in label.lower():
        print("dog")  # Output "dog" if the result is related to dog
        break

```