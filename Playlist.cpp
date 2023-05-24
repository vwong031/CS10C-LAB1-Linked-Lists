// Collaborated with: Valerie Wong, Kira Hammond, zyBook
// Demo format: https://docs.google.com/document/d/1zr-4YigDfKToSr2B6GjZVRtCb_vdE-GOfLsmqAVf25c/edit

#include "Playlist.h"
//fct good
PlaylistNode::PlaylistNode() {
  uniqueID = "none";
  songName = "none";
  artistName = "none";
  songLength = 0; 
  nextNodePtr = nullptr; 
}
// fct good
PlaylistNode::PlaylistNode(
  string id, string nameSong, string nameArtist, int lengthSong, PlaylistNode* nextNodePtr) {
  uniqueID = id;
  songName = nameSong;
  artistName = nameArtist;
  songLength = lengthSong;
  nextNodePtr = nextNodePtr;
}
// fct good
void PlaylistNode::InsertAfter(PlaylistNode* nodePtrToInsert) {
  PlaylistNode* originalNext = nextNodePtr;
  nextNodePtr = nodePtrToInsert;
  nodePtrToInsert->SetNext(originalNext);
}
// fct good
void PlaylistNode::SetNext(PlaylistNode* nodePtrToSet) {
  nextNodePtr = nodePtrToSet;
}

string PlaylistNode::GetID() const {
  return uniqueID;
}

string PlaylistNode::GetSongName() const {
  return songName;
}

string PlaylistNode::GetArtistName() const {
  return artistName;
}

int PlaylistNode::GetSongLength() const {
  return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
  return nextNodePtr;
}

const void PlaylistNode::PrintPlaylistNode() const {
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength;
  // cout << endl;
}
