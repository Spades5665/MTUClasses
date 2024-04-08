# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)       
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        # Finds the distance to the closest food
        minFood = 999999
        for foodPos in newFood.asList():
            if util.manhattanDistance(newPos, foodPos) < minFood:
                minFood = util.manhattanDistance(newPos, foodPos)

        # Finds the distance to the closest ghost
        minGhost = 999999
        for ghostPos in successorGameState.getGhostPositions():
            if util.manhattanDistance(newPos, ghostPos) < minGhost:
                minGhost = util.manhattanDistance(newPos, ghostPos)        

        # Penalizes for standing still
        penalty = 0
        if action == 'Stop':
            penalty += 100

        # If all ghosts are scared, add points so pacman isn't afraid to go through ghosts
        scaredPoints = 0
        if min(newScaredTimes) > 0:
            scaredPoints = 100


        # As minGhost increases, the score should increase since the ghost is farther away. Vice versa, when minFood decreases, the score should increase
        return successorGameState.getScore() + ((minGhost + scaredPoints) / minFood) - penalty

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

    # Returns the Action and Score taken
    def getActionScore(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Ends if the desired depth is reached or the game has ended
        if currentDepth == self.depth or gameState.isLose() or gameState.isWin():
            return "", self.evaluationFunction(gameState)
        
        # Call max for pacman
        if agentIndex == 0:
            return self.pacmanTurn(gameState, agentIndex, currentDepth, alpha, beta)

        # Other indices are ghosts
        else:
            return self.ghostTurn(gameState, agentIndex, currentDepth, alpha, beta)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        return self.getActionScore(gameState, 0, 0, 0, 0)[0]
        
    def pacmanTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the max action and score for this turn
        maxAction = ""
        maxScore = -999999

        # Loop through each of this agents actions
        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1
            
            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            if score > maxScore:
                maxScore = score
                maxAction = action

        return maxAction, maxScore

    def ghostTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the min action and score for this turn
        minAction = ""
        minScore = 999999

        # Loop through each of this agents actions
        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1
            
            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            if score < minScore:
                minScore = score
                minAction = action

        return minAction, minScore 

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        return self.getActionScore(gameState, 0, 0, -999999, 999999)[0]
        
    def pacmanTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the max action and score for this turn
        maxAction = ""
        maxScore = -999999

        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1

            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            if score > maxScore:
                maxScore = score
                maxAction = action

            if maxScore > beta:
                return maxAction, maxScore
            
            alpha = max(alpha, maxScore)
        
        return maxAction, maxScore
        
    def ghostTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the min action and score for this turn
        minAction = ""
        minScore = 999999

        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1

            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            if score < minScore:
                minScore = score
                minAction = action

            if alpha > minScore:
                return minAction, minScore 
            
            beta = min(beta, minScore)
            
        return minAction, minScore 

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        return self.getActionScore(gameState, 0, 0, 0, 0)[0]
        
    def pacmanTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the max action and score for this turn
        maxAction = ""
        maxScore = -999999

        # Loop through each of this agents actions
        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1
            
            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            if score > maxScore:
                maxScore = score
                maxAction = action

        return maxAction, maxScore

    def ghostTurn(self, gameState, agentIndex, currentDepth, alpha, beta):
        
        # Holds the min action and score for this turn
        aveAction = ""
        aveScore = 0

        # Loop through each of this agents actions
        for action in gameState.getLegalActions(agentIndex):
            nextIndex = agentIndex + 1
            nextDepth = currentDepth
        
            # Reset to pacman if all the ghosts have gone, and increases depth
            if (nextIndex == gameState.getNumAgents()):
                nextIndex = 0
                nextDepth += 1
            
            score = self.getActionScore(gameState.generateSuccessor(agentIndex, action), nextIndex, nextDepth, alpha, beta)[1]

            aveScore += score

        return aveAction, aveScore / len(gameState.getLegalActions(agentIndex))

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: 
    minFood finds the closest food to pacman, and is divided so the closer one is the more points it gets
    minGhost finds the closest ghost and is direct, so the farther one is the more points it gets
    getScore is just the score of the current state
    penalty removes points if a ghost is too close 
    len(foodList) makes it more beneficial to have less food to eat


    """
    "*** YOUR CODE HERE ***"
    pacmanPos = currentGameState.getPacmanPosition()

    # Finds the distance to the closest food
    minFood = 999999
    for foodPos in currentGameState.getFood().asList():
        if util.manhattanDistance(pacmanPos, foodPos) < minFood:
            minFood = util.manhattanDistance(pacmanPos, foodPos)

    # Finds the distance to the closest ghost
    minGhost = 999999
    for ghostPos in currentGameState.getGhostPositions():
        if util.manhattanDistance(pacmanPos, ghostPos) < minGhost:
            minGhost = util.manhattanDistance(pacmanPos, ghostPos)        

    # Tries to keep ghosts from getting to close
    penalty = 0
    if minGhost < 2:
        penalty = 1000

    # Checks if all ghosts are currently in scared mode
    scaredTimes = []
    for ghost in currentGameState.getGhostStates():
        scaredTimes.append(ghost.scaredTimer)

    scaredPoints = 0
    if min(scaredTimes) > 0:
        scaredPoints = 200

    return (currentGameState.getScore() * 100) + (((minGhost + scaredPoints) * 50) / minFood) - (len(currentGameState.getFood().asList())) - penalty

# Abbreviation
better = betterEvaluationFunction
