import pandas as pd
import argparse as arg
# make a color database to correspond with each agent FillRed, FillGreen, FillBlue, OutlineRed, OutlineGreen, OutlineBlue
# each agent must have these things: Agent, Maneuver Tactic

# switch (i % 2)
#         {
#         case 0:
#             maneuvers.push_back(new Chase());
#             maneuverNames[i] = 'c';
#             fill[i] = sf::Color::Magenta;  255, 87, 51

#             break;
#         case 1:
#             maneuvers.push_back(new Flee());
#             maneuverNames[i] = 'f';
#             fill[i] = sf::Color::Cyan; rgb(0,255,255)
#             break;
#         }

rows = 1000
agentcolumns = ['Agent', 'Maneuver', 'Tactic']
colorcolumns = ['Agent', 'FillRed', 'FillGreen', 'FillBlue', 'OutlineRed', 'OutlineGreen', 'OutlineBlue']
agents = pd.DataFrame(0, index=range(rows), columns=agentcolumns)
colors = pd.DataFrame(0, index=range(rows), columns=colorcolumns)

def make_agents(agents):
    for i in range(len(agents)):
        agents.loc[i, 'Agent'] = i
        if i % 2 == 0:
            agents.loc[i, 'Maneuver'] = 'Chase'
        else:
            agents.loc[i, 'Maneuver'] = 'Flee'
        if i % 3 == 0:
            agents.loc[i, 'Tactic'] = 'Cooperate'
        elif i % 3 == 1:
            agents.loc[i, 'Tactic'] = 'Defect'
        else:
            agents.loc[i, 'Tactic'] = 'TitForTat'
    agents.to_csv('Configs/agents.csv', index=False)

def make_colors(colors):
    for i in range(len(colors)):
        colors.loc[i, 'Agent'] = i
        if i % 2 == 0:
            colors.loc[i, 'FillRed'] = 255
            colors.loc[i, 'FillGreen'] = 0
            colors.loc[i, 'FillBlue'] = 255
        else:
            colors.loc[i, 'FillRed'] = 0
            colors.loc[i, 'FillGreen'] = 255
            colors.loc[i, 'FillBlue'] = 255
        if i % 3 == 0:
            colors.loc[i, 'OutlineRed'] = 255
            colors.loc[i, 'OutlineGreen'] = 0
            colors.loc[i, 'OutlineBlue'] = 0
        elif i % 3 == 1:
            colors.loc[i, 'OutlineRed'] = 0
            colors.loc[i, 'OutlineGreen'] = 255
            colors.loc[i, 'OutlineBlue'] = 0
        else:
            colors.loc[i, 'OutlineRed'] = 0
            colors.loc[i, 'OutlineGreen'] = 0
            colors.loc[i, 'OutlineBlue'] = 255
    colors.to_csv('Configs/colors.csv', index=False)

def make_settings():
    print('Do you want the simulation to render (Y/N)?')
    draw = input()
    if draw == 'N' or draw == 'n':
        draw = 0
    else:
        draw = 1
    print('Do you want the simulation to play games and generate data (Y/N)?')
    play = input()
    if play == 'N' or play == 'n':
        play = 0
    else:
        play = 1
    print('How many agents? (1000 max)')
    numAgents = input()
    print('Agent radius? sizes between 0.1 and 0.5 are recommended')
    agentRadius = input()
    print('Max rounds? (1000000000 max)')
    maxRounds = input()
    print('Gravity x? (0.0 recommended)')
    gravityx = input()
    print('Gravity y? (0.0 recommended)')
    gravityy = input()
    print('Time steps per frame? (1.0 recommended)')
    timeStep = input()
    print('Velocity iterations? (6 recommended)')
    velocityIterations = input()
    print('Position iterations? (2 recommended)')
    positionIterations = input()
    print('Density? (1 recommended)')
    density = input()
    print('Friction? (0.3 recommended')
    friction = input()
    print('Restitution? (0.5 recommended)')
    restitution = input()
    print('Start position x? (1 recommended)')
    startPositionx = input()
    print('Start position y? (1 recommended)')
    startPositiony = input()
    print('Start force x? (1 recommended)')
    startForcex = input()
    print('Start force y? (1 recommended)')
    startForcey = input()
    print('Speed cap? (1 recommended)')
    speedCap = input()
    print('Acceleration cap? (0.05 recommended)')
    accelerationCap = input()
    print('Window x? (40 recommended)')
    window_x = input()
    print('Window y? (30 recommended)')
    window_y = input()
    print('Frame rate? (60 recommended)')
    frameRate = input()
    timeStep = timeStep / frameRate
    return draw, play, numAgents, agentRadius, maxRounds, gravityx, gravityy, timeStep, velocityIterations, positionIterations, density, friction, restitution, startPositionx, startPositiony, startForcex, startForcey, speedCap, accelerationCap, window_x, window_y, frameRate

def make_settings_file(draw, play, numAgents, agentRadius, maxRounds, gravityx, gravityy, timeStep, velocityIterations, positionIterations, density, friction, restitution, startPositionx, startPositiony, startForcex, startForcey, speedCap, accelerationCap, window_x, window_y, frameRate):
    settings = pd.DataFrame(columns=['Setting', 'Value'])
    settings.loc[0] = ['draw', draw]
    settings.loc[1] = ['play', play]
    settings.loc[2] = ['numAgents', numAgents]
    settings.loc[3] = ['agentRadius', agentRadius]
    settings.loc[4] = ['maxrounds', maxRounds]
    settings.loc[5] = ['gravityX', gravityx]
    settings.loc[6] = ['gravityY', gravityy]
    settings.loc[7] = ['timeStep', timeStep]
    settings.loc[8] = ['velocityIterations', velocityIterations]
    settings.loc[9] = ['positionIterations', positionIterations]
    settings.loc[10] = ['density', density]
    settings.loc[11] = ['friction', friction]
    settings.loc[12] = ['restitution', restitution]
    settings.loc[13] = ['startPositionX', startPositionx]
    settings.loc[14] = ['startPositionY', startPositiony]
    settings.loc[15] = ['startForceX', startForcex]
    settings.loc[16] = ['startForceY', startForcey]
    settings.loc[17] = ['speedCap', speedCap]
    settings.loc[18] = ['accelerationCap', accelerationCap]
    settings.loc[19] = ['window_x', window_x]
    settings.loc[20] = ['window_y', window_y]
    settings.loc[21] = ['frameRate', frameRate]
    settings.to_csv('Configs/settings.csv', index=False)

    
# Create the parser
parser = arg.ArgumentParser(description="Simulation Settings")

# Add the arguments
parser.add_argument('--manual', type=str, choices=['Y', 'N'], default='N', help='Manually input settings? (Y/N)')
parser.add_argument('--draw', type=str, choices=['Y', 'N'], default='Y', help='Render the simulation? (Y/N)')
parser.add_argument('--play', type=str, choices=['Y', 'N'], default='Y', help='Play games and generate data? (Y/N)')
parser.add_argument('--numAgents', type=int, default=1000, help='Number of agents (1000 max)')
parser.add_argument('--agentRadius', type=float, default=0.3, help='Agent radius (between 0.1 and 0.5 recommended)')
parser.add_argument('--maxRounds', type=int, default=10000, help='Max rounds (1 billion max)')
parser.add_argument('--gravityx', type=float, default=0.0, help='Gravity x (0.0 recommended)')
parser.add_argument('--gravityy', type=float, default=0.0, help='Gravity y (0.0 recommended)')
parser.add_argument('--timeStep', type=float, default=1.0, help='Time steps per frame (1.0 recommended)')
parser.add_argument('--velocityIterations', type=int, default=6, help='Velocity iterations (6 recommended)')
parser.add_argument('--positionIterations', type=int, default=2, help='Position iterations (2 recommended)')
parser.add_argument('--density', type=float, default=1.0, help='Density (1.0 recommended)')
parser.add_argument('--friction', type=float, default=0.3, help='Friction (0.3 recommended)')
parser.add_argument('--restitution', type=float, default=0.5, help='Restitution (0.5 recommended)')
parser.add_argument('--startPositionx', type=float, default=1.0, help='Start position x (1.0 recommended)')
parser.add_argument('--startPositiony', type=float, default=1.0, help='Start position y (1.0 recommended)')
parser.add_argument('--startForcex', type=float, default=1.0, help='Start force x (1.0 recommended)')
parser.add_argument('--startForcey', type=float, default=1.0, help='Start force y (1.0 recommended)')
parser.add_argument('--speedCap', type=float, default=1.0, help='Speed cap (1.0 recommended)')
parser.add_argument('--accelerationCap', type=float, default=0.05, help='Acceleration cap (0.05 recommended)')
parser.add_argument('--window_x', type=int, default=40, help='Window x size (40 recommended)')
parser.add_argument('--window_y', type=int, default=30, help='Window y size (30 recommended)')
parser.add_argument('--frameRate', type=int, default=60, help='Frame rate (60 recommended)')

# Parse the arguments
args = parser.parse_args()

# turn into variables
draw = 0 if args.draw.lower() == 'n' else 1
play = 0 if args.play.lower() == 'n' else 1
numAgents = args.numAgents
agentRadius = args.agentRadius
maxRounds = args.maxRounds
gravityx = args.gravityx
gravityy = args.gravityy
timeStep = args.timeStep / args.frameRate
velocityIterations = args.velocityIterations
positionIterations = args.positionIterations
density = args.density
friction = args.friction
restitution = args.restitution
startPositionx = args.startPositionx
startPositiony = args.startPositiony
startForcex = args.startForcex
startForcey = args.startForcey
speedCap = args.speedCap
accelerationCap = args.accelerationCap
window_x = args.window_x
window_y = args.window_y
frameRate = args.frameRate

if args.manual.lower() == 'y':
    draw, play, numAgents, agentRadius, maxRounds, gravityx, gravityy, timeStep, velocityIterations, positionIterations, density, friction, restitution, startPositionx, startPositiony, startForcex, startForcey, speedCap, accelerationCap, window_x, window_y, frameRate = make_settings()


make_agents(agents)
make_colors(colors)
make_settings_file(draw, play, numAgents, agentRadius, maxRounds, gravityx, gravityy, timeStep, velocityIterations, positionIterations, density, friction, restitution, startPositionx, startPositiony, startForcex, startForcey, speedCap, accelerationCap, window_x, window_y, frameRate)
