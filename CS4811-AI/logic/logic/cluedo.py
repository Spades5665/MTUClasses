'''cluedo.py - project skeleton for a propositional reasoner
for the game of Clue.  Unimplemented portions have the comment "TO
BE IMPLEMENTED AS AN EXERCISE".  The reasoner does not include
knowledge of how many cards each player holds.
Originally by Todd Neller
Ported to Python by Dave Musicant
Adapted to course needs by Laura Brown

Copyright (C) 2008 Dave Musicant

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Information about the GNU General Public License is available online at:
  http://www.gnu.org/licenses/
To receive a copy of the GNU General Public License, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.'''

import cnf

class Cluedo:
    suspects = ['sc', 'mu', 'wh', 'gr', 'pe', 'pl']
    weapons  = ['kn', 'cs', 're', 'ro', 'pi', 'wr']
    rooms    = ['ha', 'lo', 'di', 'ki', 'ba', 'co', 'bi', 'li', 'st']
    casefile = "cf"
    hands    = suspects + [casefile]
    cards    = suspects + weapons + rooms

    """
    Return ID for player/card pair from player/card indicies
    """
    @staticmethod
    def getIdentifierFromIndicies(hand, card):
        return hand * len(Cluedo.cards) + card + 1

    """
    Return ID for player/card pair from player/card names
    """
    @staticmethod
    def getIdentifierFromNames(hand, card):
        return Cluedo.getIdentifierFromIndicies(Cluedo.hands.index(hand), Cluedo.cards.index(card))


# **************
#  Question 6 
# **************
def deal(hand, cards):
    "Construct the CNF clauses for the given cards being in the specified hand"
    "*** YOUR CODE HERE ***"
    return [[Cluedo.getIdentifierFromNames(hand, card)] for card in cards]


# **************
#  Question 7 
# **************
def axiom_card_exists():
    """
    Construct the CNF clauses which represents:
        'Each card is in at least one place'
    """
    "*** YOUR CODE HERE ***"
    result = []
    for card in Cluedo.cards:
        result.append([Cluedo.getIdentifierFromNames(hand, card) for hand in Cluedo.hands])
    return result


# **************
#  Question 7 
# **************
def axiom_card_unique():
    """
    Construct the CNF clauses which represents:
        'If a card is in one place, it can not be in another place'
    """
    "*** YOUR CODE HERE ***"
    result = []

    for card in Cluedo.cards:
        for i in range(len(Cluedo.hands) - 1):
            for j in range(i, len(Cluedo.hands)):
                result.append([-Cluedo.getIdentifierFromNames(Cluedo.hands[i], card), -Cluedo.getIdentifierFromNames(Cluedo.hands[j], card)])
    
    return result


# **************
#  Question 7 
# **************
def axiom_casefile_exists():
    """
    Construct the CNF clauses which represents:
        'At least one card of each category is in the case file'
    """
    "*** YOUR CODE HERE ***"
    return [[Cluedo.getIdentifierFromNames("cf", suspect) for suspect in Cluedo.suspects], [Cluedo.getIdentifierFromNames("cf", weapon) for weapon in Cluedo.weapons], [Cluedo.getIdentifierFromNames("cf", room) for room in Cluedo.rooms]]


# **************
#  Question 7 
# **************
def axiom_casefile_unique():
    """
    Construct the CNF clauses which represents:
        'No two cards in each category are in the case file'
    """
    "*** YOUR CODE HERE ***"
    result = []
    for i in range(len(Cluedo.suspects) - 1):
        for j in range(i, len(Cluedo.suspects)):
            result.append([-Cluedo.getIdentifierFromNames("cf", Cluedo.suspects[i]), -Cluedo.getIdentifierFromNames("cf", Cluedo.suspects[j])])

    for i in range(len(Cluedo.weapons) - 1):
        for j in range(i, len(Cluedo.weapons)):
            result.append([-Cluedo.getIdentifierFromNames("cf", Cluedo.weapons[i]), -Cluedo.getIdentifierFromNames("cf", Cluedo.weapons[j])])
    
    for i in range(len(Cluedo.rooms) - 1):
        for j in range(i, len(Cluedo.rooms)):
            result.append([-Cluedo.getIdentifierFromNames("cf", Cluedo.rooms[i]), -Cluedo.getIdentifierFromNames("cf", Cluedo.rooms[j])])
    return result


# **************
#  Question 8 
# **************
def suggest(suggester, card1, card2, card3, refuter, cardShown):
    "Construct the CNF clauses representing facts and/or clauses learned from a suggestion"
    "*** YOUR CODE HERE ***"
    result = []
    if refuter == None:
        for player in Cluedo.suspects:
            if player != suggester:
                result.append([-Cluedo.getIdentifierFromNames(player, card1)])
                result.append([-Cluedo.getIdentifierFromNames(player, card2)])
                result.append([-Cluedo.getIdentifierFromNames(player, card3)])
    elif cardShown == None:
        ind = 0
        while Cluedo.suspects[ind] != suggester:
            ind += 1

        ind += 1
        if ind == len(Cluedo.suspects):
            ind = 0

        while Cluedo.suspects[ind] != refuter:
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card1)])
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card2)])
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card3)])
            
            ind += 1
            if ind == len(Cluedo.suspects):
                ind = 0
            
        result.append([Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card1), Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card2), Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card3)])
    else:
        ind = 0
        while Cluedo.suspects[ind] != suggester:
            ind += 1

        ind += 1
        if ind == len(Cluedo.suspects):
            ind = 0
            
        while Cluedo.suspects[ind] != refuter:
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card1)])
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card2)])
            result.append([-Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], card3)])
            
            ind += 1
            if ind == len(Cluedo.suspects):
                ind = 0
            
        result.append([Cluedo.getIdentifierFromNames(Cluedo.suspects[ind], cardShown)])
    
    return result


# **************
#  Question 9 
# **************
def accuse(accuser, card1, card2, card3, correct):
    "Construct the CNF clauses representing facts and/or clauses learned from an accusation"
    "*** YOUR CODE HERE ***"
    result = []
    if correct:
        result.append([Cluedo.getIdentifierFromNames("cf", card1)])
        result.append([Cluedo.getIdentifierFromNames("cf", card2)])
        result.append([Cluedo.getIdentifierFromNames("cf", card3)])
    else:
        result.append([-Cluedo.getIdentifierFromNames("cf", card1), -Cluedo.getIdentifierFromNames("cf", card2), -Cluedo.getIdentifierFromNames("cf", card3)])

        result.append([-Cluedo.getIdentifierFromNames(accuser, card1)])
        result.append([-Cluedo.getIdentifierFromNames(accuser, card2)])
        result.append([-Cluedo.getIdentifierFromNames(accuser, card3)])

    return result
