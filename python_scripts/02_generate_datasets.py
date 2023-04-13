# %% [markdown]
# ### Generate an Input Dataset
# - Just generate N random key-value pairs
# - Keys go from 1-N, values go from 1-N (ofcourse random values)
# - Store them in the form of a JSON to make it easier to read
# - N is initially fixed to 1,000,000,000 (1 billion)

# %%
import random
import json
from tqdm import tqdm

N = 100000000

values = random.sample(range(1, N*2), N)
keys = {}

for iter in tqdm(range(1,N)):
    keys[iter] = values[iter]

json_object = json.dumps(keys, indent=4)

with open("input_data_1.json", "w") as outfile:
    outfile.write(json_object)





