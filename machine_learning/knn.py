import numpy as np

data = np.array([
	[154,1],
	[126,2],
	[70,2],
	[196,2],
	[161,2],
	[371,4]
])

print(data[0])

feature = (data[:,0])
print(feature)

label = data[:,-1]
print(label)

