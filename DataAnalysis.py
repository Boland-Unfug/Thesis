import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# TODO:
# convert game states into points for each agent DONE
# calculate scores for agents each round as a result of game actions DONE
# graph the scores by round DONE

def make_history(data, settings):
    # undo this: uint64_t historyKey = ((uint64_t)round << 32) | ((uint64_t)id1 << 16) | id2;
    # this creates the round, agent1, and agent2 columns
    data['Round'] = np.right_shift(data['Key'], 32)
    data['Agent1'] = np.bitwise_and(np.right_shift(data['Key'], 16), 0xFFFF)
    data['Agent2'] = np.bitwise_and(data['Key'], 0xFFFF)
    

    # add scores
    score_matrix = np.array([[3, 3], [0, 5], [5, 0], [1, 1]])
    data['Agent1points'] = np.zeros(len(data))
    data['Agent2points'] = np.zeros(len(data))

    for i in range(len(data)): # ordered beforehand
        data.loc[i, 'Agent1points'] = score_matrix[data.loc[i, 'Value']][0]
        data.loc[i, 'Agent2points'] = score_matrix[data.loc[i, 'Value']][1]

    # make agant1 maneuvers, agent2 maneuvers, agent 1 tactics, and agent2 tactics columns
    for i in range(len(data)):
        data.loc[i, 'Agent1maneuvers'] = settings.loc[data.loc[i, 'Agent1'], 'Maneuver']
        data.loc[i, 'Agent2maneuvers'] = settings.loc[data.loc[i, 'Agent2'], 'Maneuver']
        data.loc[i, 'Agent1tactics'] = settings.loc[data.loc[i, 'Agent1'], 'Tactic']
        data.loc[i, 'Agent2tactics'] = settings.loc[data.loc[i, 'Agent2'], 'Tactic']


    # sort data by round
    data = data.sort_values(by=['Round', 'Agent1', 'Agent2'])

    # fix the index
    data = data.reset_index(drop=True)

    return data

def make_score_history(data, settings):
    # honestly want to scrap and start again but I am so close to this part
    # I just need to change it so that the row is the agent and the column is the round but thats proving a bitch

    # get the first and last round
    first_round = data['Round'].min()
    print(first_round)
    last_round = data['Round'].max()

    # update the rounds so they start at 1
    data['Round'] = data['Round'] - first_round + 1

    # get the number of agents
    num_agents = len(settings)
    agents = settings['Agent'].values

    # make a dataframe of size max - min X num_agents
    # initialize the scores to 0
    scores = pd.DataFrame(np.zeros((num_agents,last_round-first_round + 1 )), index=agents, columns=range(first_round, last_round+1))

    print(scores)

    # Go through each history row
    # Add the points to the scores by agent and round
    for i in range(len(data)):
        round = data['Round'][i]
        agent1 = data['Agent1'][i]
        agent2 = data['Agent2'][i]
        agent1points = data['Agent1points'][i]
        agent2points = data['Agent2points'][i]

        # Set all the scores for the round to the previous round
        if round > 1:
            scores.iloc[round-1] = scores.iloc[round-2]
        
        # Update scores for both agents in the given round
        scores.at[agent1, round-1] += agent1points
        scores.at[agent2, round-1] += agent2points

    print(scores)
    return scores

def plot_scores(scores, settings):
    # match the line color to the tactic
    # defect is red, cooperate is green
    # tit for tat is blue, naive is purple
    colors = ['red'] * len(settings)  # Initialize the colors array based on the number of rows in scores
    for i in range(len(settings)):  # Iterate through the rows of the DataFrame
        if settings.loc[i, 'Tactic'] == 'd':
            colors[i] = 'red'
        elif settings.loc[i, 'Tactic'] == 'c':
            colors[i] = 'green'
        elif settings.loc[i, 'Tactic'] == 't':
            colors[i] = 'blue'
        elif settings.loc[i, 'Tactic'] == 'n':
            colors[i] = 'purple'

    print(scores.shape)
    plt.plot(scores, color=colors, label=f'Line {i+1}')

    plt.xlabel('X axis')
    plt.ylabel('Y axis')
    plt.legend()
    plt.show()




# Load the data
history = pd.read_csv('Data/history.csv')
settings = pd.read_csv('Data/gamesettings.csv')
history = make_history(history, settings)
scores = make_score_history(history, settings)
plot_scores(scores, settings)