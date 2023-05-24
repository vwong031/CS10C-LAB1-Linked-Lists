// Collaborated with: Valerie Wong, Kira Hammond, zyBook
// Demo format: https://docs.google.com/document/d/1zr-4YigDfKToSr2B6GjZVRtCb_vdE-GOfLsmqAVf25c/edit

#include <iostream>
using namespace std;

#include "Playlist.h"

void PrintMenu(string);
PlaylistNode* AddSong(PlaylistNode*);
PlaylistNode* RemoveSongWithID(PlaylistNode*, PlaylistNode*, string, bool, string&);
PlaylistNode* RemoveSong(PlaylistNode*, PlaylistNode*);
PlaylistNode* ChangePositionOfSong(PlaylistNode*, PlaylistNode*);
void OutputSongsBySpecificArtist(PlaylistNode*);
void OutputTotalTimeOfPlaylist(PlaylistNode*);
void OutputFullPlaylist(string, PlaylistNode*);


int main() {
  string playlistTitle;
  PlaylistNode* head = new PlaylistNode;
  PlaylistNode* tail = head;
  char option;

  cout << "Enter playlist's title:" << endl; 
  getline(cin, playlistTitle);
  cout << endl;

  do {
    PrintMenu(playlistTitle);
    cin >> option;

    // ignore the newline or space immediatly after user's input
    //   in case the next input is getline(cin, ...)
    //   as in outputSongsBySpecificArtist()
    cin.ignore();
    
    switch (option) {
      case 'a' :
        tail = AddSong(tail);
        break;
        // Note: This "break;" makes it so that we break out of the switch statement,
        // continuing below the closing curly brace
      case 'd' :
        tail = RemoveSong(head, tail); 
        break;
      case 'c' :
        tail = ChangePositionOfSong(head, tail);
        break;
      case 's' :
        OutputSongsBySpecificArtist(head);
        break;
      case 't' :
        OutputTotalTimeOfPlaylist(head);
        break;
      case 'o' :
        OutputFullPlaylist(playlistTitle, head);
        break;
      case 'q' :
        break;
      default :
        // Note: This default block runs if none of the above cases match
        // (i.e. option is not 'a', not 'd', not 'c', etc.)
        cout << "'" << option << "' is not a valid option." << endl << endl;
    }
  } while (option != 'q');

  return 0;
}


void PrintMenu(string playlistTitle) {
  cout << playlistTitle << " PLAYLIST MENU" << endl; 
  cout << "a - Add song" << endl
    << "d - Remove song" << endl
    << "c - Change position of song" << endl 
    << "s - Output songs by specific artist" << endl
    << "t - Output total time of playlist (in seconds)" << endl
    << "o - Output full playlist" << endl
    << "q - Quit" << endl; 

  cout << endl; 
  cout << "Choose an option:" << endl; 
}


PlaylistNode* AddSong(PlaylistNode* originalTail) {
  // pointers, new, delete:
  // https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/1/section/7

  PlaylistNode* song;
  PlaylistNode* newTail;
  string id;
  string songName;
  string artistName;
  int songLength;

  cout << "ADD SONG" << endl;

  cout << "Enter song's unique ID:" << endl;
  cin >> id;

  cout << "Enter song's name:" << endl;
  cin.ignore();
  getline(cin, songName);

  cout << "Enter artist's name:" << endl;
  getline(cin, artistName);

  /* Note: With the current implementation, the songLength can be negative
     Also: If the user inputs a non-integer, the program enters an infinite loop
  */
  cout << "Enter song's length (in seconds):" << endl;
  cin >> songLength;

  // point song at a newly created PlaylistNode in memory
  song = new PlaylistNode(id, songName, artistName, songLength);
  
  // "append" the newly created PlaylistNode after what was the last node in the linked list
  originalTail->InsertAfter(song);

  // tell the function's user where to find what is now the last node in the linked list
  newTail = song;

  cout << endl;

  return newTail;
}


PlaylistNode* RemoveSongWithID(PlaylistNode* head, PlaylistNode* originalTail, string id, bool shouldDeleteFromMemory, string& songName) {
  /* Note: If two songs have the same ID, only the first is removed. */

  PlaylistNode* previous = nullptr;
  PlaylistNode* current = nullptr;
  PlaylistNode* next = nullptr;
  PlaylistNode* newTail = originalTail;

  previous = head;
  current = previous->GetNext();

  while (current != nullptr) {
    next = current->GetNext();   // nullptr if removing last song
    if (id == current->GetID()) {
      songName = current->GetSongName();
      previous->SetNext(next);
      if (next == nullptr) {
        // The node being removed is the originalTail
        newTail = previous;
      }
      if (shouldDeleteFromMemory) {
        // If the song is removed by the user, delete from memory
        // If the song is removed to move it somewhere else, don't delete
        delete current;
      }
      current = nullptr;
      break;
    }
    else {
      previous = current;
      current = next;
    }
  }

  return newTail;
}

// 
PlaylistNode* RemoveSong(PlaylistNode* head, PlaylistNode* originalTail) {
  // TODO: Test removing the head, removing the tail, removing from the middle,
  // removing something that doesn't exist, removing from empty list,
  // removing from list with 0/1/2/3/10 elements
  
  string id;
  string songName = "";
  PlaylistNode* newTail;

  cout << "REMOVE SONG" << endl;
  cout << "Enter song's unique ID:" << endl;
  cin >> id;

  newTail = RemoveSongWithID(head, originalTail, id, true, songName);

  if (songName == "") {
    cout << "No song with ID \"" << id << "\"." << endl;
  }
  else {
    cout << "\"" << songName << "\" removed." << endl;
  }
  
  cout << endl;

  return newTail;
}


PlaylistNode* ChangePositionOfSong(PlaylistNode *head, PlaylistNode *originalTail) {
  // TODO:

  // Test 1,  3:   1 2 3 4     ->   2 3 1 4      move head node
  // Test 5,  2:   1 2 3 4 5   ->   1 5 2 3 4    move tail node
  // Test 5,  1:   1 2 3 4 5   ->   5 1 2 3 4    move to head
  // Test 2,  5:   1 2 3 4 5   ->   1 3 4 5 2    move to tail
  // Test 3,  2:   1 2 3 4     ->   1 3 2 4      move up
  // Test 2,  4:   1 2 3 4 5   ->   1 3 4 2 5    move down

  // Test 3,  0:   1 2 3 4     ->   3 1 2 4      move to < first
  // Test 3, 10:   1 2 3 4     ->   1 2 4 3      move to > last

  int currentPosition; 
  int newPosition; 
  int totalNodes;
  int i;
  PlaylistNode *tmp = nullptr;
  PlaylistNode *holder = nullptr; 
  PlaylistNode *nodeToMove = nullptr;
  PlaylistNode *newTail = originalTail;
  string idOfNodeToMove;
  string songNameToDiscard = "";
  
  cout << "CHANGE POSITION OF SONG" << endl; 

  cout << "Enter song's current position:" << endl; 
  cin >> currentPosition;

  cout << "Enter new position for song:" << endl; 
  cin >> newPosition; 

  // 1. find node the user wants to move (nodeToMove)
  // 2. count nodes in linked list (totalNodes)
  tmp = head;
  i = 0;
  while (tmp->GetNext() != nullptr) {
    i++;
    tmp = tmp->GetNext();
    if (i == currentPosition) {
      nodeToMove = tmp;
    }
  }
  totalNodes = i;

  idOfNodeToMove = nodeToMove->GetID();

  if (newPosition < 1) {
    newPosition = 1;
  }
  else if (newPosition > totalNodes) {
    newPosition = totalNodes; 
  }
  
  // find node directly before the position the user wants to move to
  newTail = RemoveSongWithID(head, originalTail, idOfNodeToMove, false, songNameToDiscard);
  holder = head;
  for (int i = 1; i <= newPosition - 1; ++i) {
    holder = holder->GetNext();
  }
  holder->InsertAfter(nodeToMove);

  cout << "\"" << nodeToMove->GetSongName() << "\""
       << " moved to position " << newPosition << endl; 

  cout << endl; 

  return newTail;
}


void OutputSongsBySpecificArtist(PlaylistNode* head) {
  // TODO: Test artist with 1 song, multiple songs, no songs

  PlaylistNode* song;
  string artistName;
  unsigned int counter;

  cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;

  cout << "Enter artist's name:" << endl;
  getline(cin, artistName);

  counter = 1;
  song = head;
  song = song->GetNext();
  while (song != nullptr) {
    if (artistName == song->GetArtistName()) {
      cout << endl << counter << "." << endl;
      song->PrintPlaylistNode();
      cout << endl;
    }
    counter++;
    song = song->GetNext();
  }

  cout << endl;
}


void OutputTotalTimeOfPlaylist(PlaylistNode *head) {
  // TODO: Test when 0, 1, 500+
  PlaylistNode *tmp;
  int totalTime = 0;

  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl; 

  cout << "Total time: ";

  tmp = head;
  while (tmp != nullptr) {
    totalTime += tmp->GetSongLength();
    tmp = tmp->GetNext();
  }

  cout << totalTime << " seconds" << endl << endl; 
  
}


//
void OutputFullPlaylist(string title, PlaylistNode *head) {
  // TODO: Test when empty, 1, 2, 5-10+
  PlaylistNode *song = head;
  int counter = 0;
  song = song->GetNext();

  cout << title << " - OUTPUT FULL PLAYLIST" << endl; 

  if (song == nullptr) {
    cout << "Playlist is empty" << endl << endl; 
  }
  else {
    while(song != nullptr) {
      ++counter;
      cout << counter << "." << endl;
      song->PrintPlaylistNode();
      song = song->GetNext(); 
      cout << endl << endl; 
    }
  }
}
