#include<iostream>
#include<Windows.h>
#include"MMSystem.h"
#include<cstdlib>
using namespace std;

class Node {
public:
    string name;
    string song_writer;
    Node* next;
    Node* prev;
    Node(string n, string s) {
        name = n;
        song_writer = s;
        next = NULL;
        prev = NULL;
    }
};

class Stack {
public:
    Node* head;
    Node* top;
    Stack() {
        head = NULL;
        top = NULL;
    }
    bool isEmpty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }
    void push(string n, string a) {
        Node* new_node = new Node(n, a);
        if (head == NULL) {
            head = new_node;
            top = new_node;
        }
        else {
            top->next = new_node;
            new_node->prev = top;
            top = new_node;
        }
    }
    void pop() {
        if (isEmpty()) {
            cout << "No song was recently played" << endl;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->prev->next = NULL;
        }
    }
    Node* Top() {
        if (isEmpty()) {
            cout << "No songs were recently played" << endl;
            return NULL;
        }
        else {
            return top;
        }
    }
    void traverse() {
        if (isEmpty()) {
            cout << "No songs were recently played" << endl;
            return;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                cout << "Song: " << temp->name << endl;
                cout << "Artist: " << temp->song_writer << endl;
                temp = temp->next;
            }
        }
    }
};

class Queue {
public:
    Node* head;
    Queue() {
        head = NULL;
    }
    bool isEmpty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }
    void enqueue(string n, string a) {
        Node* new_node = new Node(n, a);
        if (head == NULL) {
            head = new_node;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->prev = temp;
        }
    }
    void dequeue(string n) {
        if (isEmpty()) {
            cout << "There are no favourite songs" << endl;
            return;
        }
        else {
            if (head->name == n) {
                if (head->next) {
                    head->next->prev = NULL;
                    head = head->next;
                }
                else {
                    head = NULL;
                }
                return;
            }
            Node* temp = head;
            while (temp != NULL) {
                if (temp->name == n) {
                    if (temp->next) {
                        temp->next->prev = temp->prev;
                        temp->prev->next = temp->next;
                    }
                    else {
                        temp->prev->next = NULL;
                    }
                }
                temp = temp->next;
            }
        }
    }
    void traverse() {
        Node* temp = head;
        while (temp != NULL) {
            cout << "Song: " << temp->name << endl;
            cout << "Artist: " << temp->song_writer << endl;
            temp = temp->next;
        }
    }
    void playsongs(Stack& S,Stack& history) {
        Node* temp = head;
        while (1) {
            string songname = temp->name + ".wav";
            const char* csongname = songname.c_str();
            cout << endl;
            cout << "The song playing right now is : " << temp->name << endl;
            while(1){
                PlaySound(TEXT(csongname), NULL, SND_ASYNC | SND_NODEFAULT);
                cout << "Enter 'P' to Pause, 'S' to Stop, 'N' for Next, 'O' for previous, Any other key to continue: ";
                char option;
                cin >> option;
                if (option == 'p' || option == 'P') {
                    PlaySound(NULL, NULL, 0); // Pause the song
                    cout << "Song paused. Enter 'R' to resume, 'S' to stop: ";
                    cin >> option;
                    if (option == 'r' || option == 'R')
                        continue;
                    }
                if (option == 'S' || option == 's') {
            	    PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	    history.push(temp->name, temp->song_writer);
            	    S.push(temp->name, temp->song_writer);
            	    return;
                }
                if (option == 'N' || option == 'N') {
            	    if(temp->next){
						history.push(temp->name, temp->song_writer);
            	        S.push(temp->name, temp->song_writer);
            	        temp = temp->next;
            	        break;
            	    }
            	    else{
            	    	cout<<"Next not available, please proceed to previous first"<<endl;
            	        continue;
					}
                }
                if (option == 'O' || option == 'o') {
                	if(temp->prev){
                        history.push(temp->name, temp->song_writer);
                        S.push(temp->name, temp->song_writer);
                	    temp = temp->prev;
                	    break;
                    }
                    else{
                    	cout<<"Previous not available, please proceed to next first"<<endl;
                    	continue;
					}
				}
                else{
                	if(temp->next){
                	    temp = temp->next;
                	    break;
                    }
                    else{
                    	cout<<"All songs in playlist are played"<<endl;
                    	return;
					}
			    }
            }
        }
    }
};

class MusicPlayer {
    Node* head;
    int numsongs;
    Stack S;
    Stack history;
    Queue Q;
public:
    MusicPlayer() {
        head = NULL;
        numsongs = 0;
    }
    void add_song(string name, string artist) {
        Node* new_node = new Node(name, artist);
        numsongs++;
        if (head == NULL) {
            head = new_node;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->prev = temp;
            new_node->next = NULL;
        }
    }
    void remove_song(string name) {
        if (head == NULL) {
            cout << "Playlist does not exist" << endl;
        }
        else {
            if (head->name == name) {
                head = head->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
                numsongs--;
            }
            else {
                Node* temp = head;
                while (temp->name != name) {
                    temp = temp->next;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                numsongs--;
            }
        }
    }
    void displaysongs() {
        if (head == NULL) {
            cout << "Your Playlist is empty" << endl;
            return;
        }
        Node* temp = head;
        while (temp != NULL) {
            cout << "Songs name:" << temp->name << endl;
            cout << "Song Artist: " << temp->song_writer << endl;
            temp = temp->next;
        }
    }
    void Search_Songwriter(string writer) {
        if (head == NULL) {
            cout << "Your Playlist is empty" << endl;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                if (temp->song_writer == writer) {
                    cout << "Song name: " << temp->name << endl;
                    cout << "Song artist name: " << temp->song_writer << endl;
                }
                temp = temp->next;
            }
        }
    }
    void search_song(string songname) {
        if (head == NULL) {
            cout << "Your playlist is empty" << endl;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                if (temp->name == songname) {
                    cout << "Song name:" << temp->name << endl;
                    cout << "Song artist name: " << temp->song_writer << endl;
                }
                temp = temp->next;
            }
        }
    }
    void play_repeat() {
        if (S.isEmpty()) {
            cout << "No song was recently played" << endl;
            return;
        }
        string songname = S.Top()->name + ".wav";
        const char* csongname = songname.c_str();
        cout << endl;
        cout << "The song playing right now is : " << S.Top()->name << endl;
        while(1){
            PlaySound(TEXT(csongname), NULL, SND_ASYNC | SND_NODEFAULT);
            cout << "Enter 'P' to Pause or 'S' to Stop, Any other key to continue: ";
            char option;
            cin >> option;
            if (option == 'p' || option == 'P') {
                PlaySound(NULL, NULL, 0); // Pause the song
                cout << "Song paused. Enter 'R' to resume, 'S' to stop: ";
                cin >> option;
                if (option == 'r' || option == 'R')
                    continue;
                }
               if (option == 'S' || option == 's') {
            	PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	break;
            }
            else{
            	break;
			}
        }
        system("pause");
        history.push(S.Top()->name, S.Top()->song_writer);
    }
    void play_previous() {
        if (S.isEmpty()) {
            cout << "No song was recently played" << endl;
            return;
        }
        while(S.top){
            string songname = S.Top()->name + ".wav";
            const char* csongname = songname.c_str();
            cout << endl;
            cout << "The song playing right now is : " << S.Top()->name << endl;
            while(1){
                PlaySound(TEXT(csongname), NULL, SND_ASYNC | SND_NODEFAULT);
                cout << "Enter 'P' to Pause, 'S' to Stop, 'N' for Next, 'O' for previous, Any other key to continue: ";
                char option;
                cin >> option;
                if (option == 'p' || option == 'P') {
                    PlaySound(NULL, NULL, 0); // Pause the song
                    cout << "Song paused. Enter 'R' to resume, 'S' to stop: ";
                    cin >> option;
                    if (option == 'r' || option == 'R')
                        continue;
                    }
                if (option == 'S' || option == 's') {
            	    PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	    system("pause");
            	    history.push(S.Top()->name, S.Top()->song_writer);
            	    while(S.top->next)
                        S.top = S.top -> next;
            	    return;
                }
                if (option == 'N' || option == 'N') {
            	    if(S.top->next){
            	    	PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	        system("pause");
                        history.push(S.Top()->name, S.Top()->song_writer);
            	        S.top = S.top->next;
            	        break;
            	    }
            	    else{
            	    	cout<<"Next not available, please proceed to previous first"<<endl;
            	        continue;
					}
                }
                if (option == 'O' || option == 'o') {
                	if(S.top->prev){
                		PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	        system("pause");
                        history.push(S.Top()->name, S.Top()->song_writer);
                	    S.top = S.top->prev;
                	    break;
                    }
                    else{
                    	cout<<"Previous not available, please proceed to next first"<<endl;
                    	continue;
					}
				}
                else{
                	if(S.top->prev){
                	    S.top = S.top->prev;
                	    break;
                    }
                    else{
                    	cout<<"All previous songs are played"<<endl;
                    	while(S.top->next)
                            S.top = S.top -> next;
                    	return;
					}
			    }
            }
        }
    }
    void show_history() {
        if (history.isEmpty()) {
            cout << "No songs were recently played" << endl;
            return;
        }
        history.traverse();
    }
    void playsong(string songname) {
        int n = 0;
        if (head == NULL) {
            cout << "Your playlist is empty" << endl;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                if (temp->name == songname) {
                    string songname = temp->name + ".wav";
                    
                    const char* csongname = songname.c_str();
                    cout << endl;
                    cout << "The song playing right now is : " << temp->name << endl;
                    PlaySound(TEXT(csongname), NULL, SND_SYNC | SND_NODEFAULT);
                    system("pause");
                    S.push(temp->name, temp->song_writer);
                    history.push(temp->name, temp->song_writer);
                }
                else {
                    n++;
                }
                temp = temp->next;
            }
            if (n == numsongs) {
                cout << "The song does not exist in the playlist" << endl;
            }
        }
    }
    void playsongs() {
        if (head == NULL) {
            cout << "Your playlist is empty" << endl;
            cout << "Add songs in the playlist to play some songs" << endl;
            return;
        }
        Node* temp = head;
        while (1) {
            string songname = temp->name + ".wav";
            const char* csongname = songname.c_str();
            cout << endl;
            cout << "The song playing right now is : " << temp->name << endl;
            while(1){
                PlaySound(TEXT(csongname), NULL, SND_ASYNC | SND_NODEFAULT);
                cout << "Enter 'P' to Pause, 'S' to Stop, 'N' for Next, 'O' for previous, Any other key to continue: ";
                char option;
                cin >> option;
                if (option == 'p' || option == 'P') {
                    PlaySound(NULL, NULL, 0); // Pause the song
                    cout << "Song paused. Enter 'R' to resume, 'S' to stop: ";
                    cin >> option;
                    if (option == 'r' || option == 'R')
                        continue;
                    }
                if (option == 'S' || option == 's') {
            	    PlaySound(NULL, NULL, SND_ASYNC | SND_NODEFAULT);
            	    history.push(temp->name, temp->song_writer);
            	    S.push(temp->name, temp->song_writer);
            	    return;
                }
                if (option == 'N' || option == 'N') {
            	    if(temp->next){
						history.push(temp->name, temp->song_writer);
            	        S.push(temp->name, temp->song_writer);
            	        temp = temp->next;
            	        break;
            	    }
            	    else{
            	    	cout<<"Next not available, please proceed to previous first"<<endl;
            	        continue;
					}
                }
                if (option == 'O' || option == 'o') {
                	if(temp->prev){
                        history.push(temp->name, temp->song_writer);
                        S.push(temp->name, temp->song_writer);
                	    temp = temp->prev;
                	    break;
                    }
                    else{
                    	cout<<"Previous not available, please proceed to next first"<<endl;
                    	continue;
					}
				}
                else{
                	if(temp->next){
                	    temp = temp->next;
                	    break;
                    }
                    else{
                    	cout<<"All songs in playlist are played"<<endl;
                    	return;
					}
			    }
            }
        }
    }
    void show_favourites() {
        if (Q.isEmpty()) {
            cout << "There are no songs in Favourties" << endl;
            return;
        }
        else {
            Q.traverse();
        }
    }
    void favourite_song(string n) {
        if (head == NULL) {
            cout << "Your playlist is empty" << endl;
            return;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                if (temp->name == n) {
                    Q.enqueue(temp->name, temp->song_writer);
                    return;
                }
                temp = temp->next;
            }
            cout << "The song does not exist in the Playlist" << endl;
        }
    }
    void play_favourite() {
        Q.playsongs(S,history);
    }
    void remove_favourites(string n) {
        if (Q.isEmpty()) {
            cout << "There are no songs in Favourties" << endl;
            return;
        }
        else {
            Q.dequeue(n);
        }
    }
    void totalsongs() {
        cout << "Total songs in your Playlist: " << numsongs << endl;
    }
    void clearplaylist() {
        if (head == NULL) {
            cout << "Playlist does not exist " << endl;
            return;
        }
        Node* temp = head;
        while (temp != NULL) {
            Node* nextnode = temp->next;
            delete temp;
            temp = nextnode;
        }
        head = NULL;
        cout << "Playlist cleared" << endl;
        numsongs = 0;
    }
};

int main() {
    MusicPlayer M;
    string allsongs[10][2] = { "ez4ence", "ence","Rock","thechugz","Santa","MrDrek","Claps","Joker","Funk","Enimem","Creative","Halland","chilling","IceCold","Bells","Jingle","Chill","saad","good night","Khubaib" };
    string song, artist;
    int n;
    while(1){
    	cout << "All the songs in the web" << endl;
  		for (int i = 0; i < 10; i++) {
        	cout << i + 1 << ") Name:" << allsongs[i][0] << endl;
        	cout << "Artist:" << allsongs[i][1] << endl;
    	}
    	cout << endl << endl;
        char a;
        cout << "Menu" << endl;
        cout << "Enter A to add a song in the playlist" << endl;
  		cout << "Enter B to remove a song from the playlist" << endl;
  		cout << "Enter C to display the songs in the playlist" << endl;
  	    cout << "Enter D to display the songs of an artist" << endl;
  	    cout << "Enter E to search a song in the Playlist" << endl;
  		cout << "Enter F to play songs in the Playlist" << endl;
    	cout << "Enter G to see the total number of songs in the Playlist" << endl;
    	cout << "Enter H to clear the Playlist" << endl;
    	cout << "Enter I to play a song from the Playlist" << endl;
    	cout << "Enter J to repeat previously played song from the Playlist" << endl;
    	cout << "Enter K to play all the previously played song from the Playlist" << endl;
    	cout << "Enter L to show the history of the played songs from the Playlist" << endl;
    	cout << "Enter M to add a song to favourites" << endl;
    	cout << "Enter N to show the favourite songs" << endl;
    	cout << "Enter O remove a song from the favourites" << endl;
    	cout << "Enter P to play songs from the favourites" << endl;
    	cout << "Enter Q to exit" << endl;
        cin >> a;
        switch(a){
        	case 'A':
           	 	cout << "Enter the number of the song you would like to add to your playlist:";
           		cin >> n;
            	M.add_song(allsongs[n - 1][0], allsongs[n - 1][1]);
            	cout << allsongs[n - 1][0] << " was added in the Playlist" << endl;
            	Sleep(1500);
            	break;
        	case 'B':
        		cout << "Enter the name of the song you would like to remove from the playlist:";
        		cin >> song;
        		M.remove_song(song);
        		cout << song << " was removed from the Playlist" << endl;
        		Sleep(1500);
            	break;
        	case 'C':
        		M.displaysongs();
        		Sleep(1500);
            	break;
        	case 'D':
				cout << "Enter the name of the artist you would like to search the songs of in your playlist:";
        		cin >> artist;
        		M.Search_Songwriter(artist);
        		Sleep(1500);
        		break;
    		case 'E':
    			cout << "Enter the name of the song you would like to search from your playlist:";
        		cin >> song;
        		M.search_song(song);
        		Sleep(1500);
        		break;
       		case 'F':
        		M.playsongs();
        		break;
       	 	case 'G':
        		M.totalsongs();
        		Sleep(1500);
        	    break;
        	case 'H':
				M.clearplaylist();
				Sleep(1500);
        		break;
        	case 'I':
        		cout << "Enter the name of the song you want to play from the playlist:";
        		cin >> song;
        		M.playsong(song);
        		break;
        	case 'J':
        		M.play_repeat();
        		break;
        	case 'K':
        		M.play_previous();
        		break;
        	case 'L':
        		M.show_history();
        		Sleep(1500);
        		break;
        	case 'M':
        		cout << "Enter the name of the song you want to add in the favourites" << endl;
        		cin >> song;
        		M.favourite_song(song);
        		cout << "Song was added in the favourites" << endl;
        		Sleep(1500);
        		break;
        	case 'N':
        		cout << "Favourite songs" << endl;
        		M.show_favourites();
        		Sleep(1500);
        		break;
        	case 'O':
        		cout << "Enter the name of the song you want to remove from the favourites" << endl;
        		cin >> song;
        		M.remove_favourites(song);
        		cout << song << " was removed from favourites" << endl;
        		Sleep(1500);
        		break;
        	case 'P':
        		M.play_favourite();
        		break;
        	case 'Q':
        		cout<<"The Program has been exited"<<endl;
        		Sleep(1500);
        		exit(1);
        	default:
        		cout << "Please select from the given options" << endl;
        		Sleep(1500);
        		break;
    	}
    	system("CLS");
	}	
}
