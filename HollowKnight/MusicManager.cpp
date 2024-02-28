#include "MusicManager.h"
#include <iostream>

void MusicManager::Play(const string& _path)
{
	if (_path == "") return;

	MusicData* _musicData = Get(_path);

	if (!_musicData)
	{
		_musicData = new MusicData(_path);
		if (!_musicData->openFromFile("Assets/Musics/" + _path))
		{
			cerr << "Le son n'a pas �t� correctement charg�e !" << endl;
			return;
		}
	}

	if (_musicData)
	{
		_musicData->setVolume(5.0f);
		_musicData->play();
	}
}
