// Collaborated with: Valerie Wong, Kira Hammond, zyBook
// Demo format: https://docs.google.com/document/d/1zr-4YigDfKToSr2B6GjZVRtCb_vdE-GOfLsmqAVf25c/edit

#ifndef PLAYLIST_NODE_
#define PLAYLIST_NODE_

#include <iostream>
#include <string>
using namespace std;

class PlaylistNode {
public:
  PlaylistNode();
  PlaylistNode(string, string, string, int, PlaylistNode* nextNodePtr = nullptr);
  // How do you do a default value for a parameter in C++?
  void InsertAfter(PlaylistNode* nodePtrToInsert);
  void SetNext(PlaylistNode* nodePtrToSet);
  string GetID() const;
  string GetSongName() const;
  string GetArtistName() const;
  int GetSongLength() const;
  PlaylistNode* GetNext() const;
  const void PrintPlaylistNode() const;
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength; 
    PlaylistNode *nextNodePtr;
    // What does nextNodePtr do?? What is it keeping track of?
    
    // nextNodePtr keeps track of what's next in the linked list
    // So if we have a linked list of pointers song1, song2, song3
    // then song1's nextNodePtr would be song2
    // Does that help? :)
};

#endif
