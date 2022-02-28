import re
import string
import os.path
from os import path


def CountAll():
    #open text file in read mode
    text = open("input.txt", "r")

    #create dictionary for matching words
    dictionary = dict()

    #check each line of file
    for line in text:
        #remove any spaces 
        line = line.strip()

        #convert characters to lowercase
        word = line.lower()
        
        #check if the word is already in the dictionary
        if word in dictionary:
            #number of instances of word
            dictionary[word] = dictionary[word] + 1
        else:
            #if the word is not in the dictionary, add it w/ a value of 1
            dictionary[word] = 1

    #print dictionary
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    #close text file
    text.close()


def CountInstances(searchTerm):

    #convert characters to lowercase
    searchTerm = searchTerm.lower()

    #open the text file in read mode
    text = open("input.txt", "r")

    #word count variable
    wordCount = 0

    #check each line of the input file
    for line in text:
        #remove any spaces
        line = line.strip()

        #convert characters to lowercase
        word = line.lower()
        
        #check if found word is equal to the input
        if word == searchTerm:
            #word count increment
            wordCount += 1

    #Return the number of times the search term was found
    return wordCount

    #close text file
    text.close()



def CollectData():
    #open the text file
    text = open("input.txt", "r")

    #create / open frequency file
    frequency = open("frequency.dat", "w")

    #create empty dictionary
    dictionary = dict()

    #Check each line of the input file
    for line in text:
        #remove any spaces
        line = line.strip()

        #convert characters to lowercase
        word = line.lower()
        
        #check if the word is already in the dictionary
        if word in dictionary:
            #number of times word appears 
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not in the dictionary add it with value of 1
            dictionary[word] = 1

    #write each key and value pair to frequency.dat
    for key in list (dictionary.keys()):
        #format the key-value pair as strings
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    #close the opened files
    text.close()
    frequency.close()