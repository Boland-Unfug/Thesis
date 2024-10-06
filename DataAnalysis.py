import pandas as pd
import numpy as np


# TODO:
# convert game states into game actions
# calculate scores for agents each round as a result of game actions
# graph the scores by round

def make_history(data):
    # undo this: uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;
    data['Round'] = np.right_shift(data['Key'], 32)
    data['Agent1'] = np.bitwise_and(np.right_shift(data['Key'], 16), 0xFFFF)
    data['Agent2'] = np.bitwise_and(data['Key'], 0xFFFF)
    

    # add scores
    score_matrix = np.array([[1, 1], [5, 0], [0, 5], [3, 3]])
    data['Agent1points'] = np.zeros(len(data))
    data['Agent2points'] = np.zeros(len(data))

    for i in range(len(data)): # ordered beforehand
        data['Agent1points'][i] = score_matrix[data['Value'][i]][0]
        data['Agent2points'][i] = score_matrix[data['Value'][i]][1]


    # sort data by round
    data = data.sort_values(by=['Round', 'Agent1', 'Agent2'])

    # fix the index
    data = data.reset_index(drop=True)

    return data

# Load the data
history = pd.read_csv('Data/history.csv')
history = make_history(history)
settings = pd.read_csv('Data/gamesettings.csv')

# get the first and last round
first_round = history['Round'].min()
last_round = history['Round'].max()

# get the number of agents
agents = settings['Agent'].unique()
num_agents = len(agents) # this is done poorly, it counts the title but that offsets the -1 that len applies

# make a dataframe of size max - min X num_agents
# initialize the scores to 0
scores = pd.DataFrame(np.zeros((last_round, num_agents)), columns=agents)

# go through each history row
# add the points to the scores by agent and round
for i in range(len(history)):
    round = history['Round'][i]
    agent1 = history['Agent1'][i]
    agent2 = history['Agent2'][i]
    agent1points = history['Agent1points'][i]
    agent2points = history['Agent2points'][i]

    scores[agent1][round-1] += agent1points
    scores[agent2][round-1] += agent2points

# graph the scores
import matplotlib.pyplot as plt
for agent in agents:
    plt.plot(scores[agent], label=agent)
plt.legend()
plt.show()


print(history)
print(scores)








