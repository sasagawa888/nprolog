# Python Library to use TensorFlow
under construction

# Install Tensorflow

```
sudo apt install python3-pip
pip install tensorflow-cpu

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