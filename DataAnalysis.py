import pandas as pd
import numpy as np

# Load the data
data = pd.read_csv('Data/history.csv')
pd.set_option('display.max_rows', 1000)

# Display the first few rows of the data
# print(data.head())

# undo this: uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;
data['Round'] = np.right_shift(data['Key'], 32)
data['Agent1'] = np.bitwise_and(np.right_shift(data['Key'], 16), 0xFFFF)
data['Agent2'] = np.bitwise_and(data['Key'], 0xFFFF)

# sort data by round
data = data.sort_values(by=['Round', 'Agent1', 'Agent2'])

# convert the values to integers by checking their binaries
# NUL = 0
# SOH = 1
# STX = 2
# ETX = 3
for i in range(1, 88):
    if (data['Value'][i] == 'NUL'):
        data['Value'][i] = 0
    elif (data['Value'][i] == 0b00000001):
        data['Value'][i] = 1
    elif (data['Value'][i] == 0b00000010):
        data['Value'][i] = 2
    elif (data['Value'][i] == 0b00000011):
        data['Value'][i] = 3
# if data['Value'][]
print(data['Value'])
# data['Value'] = data['Value'].apply(lambda x: 0 if x == 0b00000000 else 1 if x == 0b00000001 else 2 if x == 0b00000010 else 3 if x == 0b00000011 else 4)



print(data)
# get graphing
    # see which movement strat is best
    # see which