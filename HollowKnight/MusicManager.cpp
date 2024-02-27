#include "MusicManager.h"

void MusicManager::Play(const string& _path)
{

	if (_path == "") return;

	MusicData* _musicData = Get(_path);

	if (!_musicData)
	{
		_musicData = new MusicData(_path);
		if (!_musicData->openFromFile(_path))
		{
			cerr << "Le son n'a pas �t� correctement charg�e !" << endl;
			return;
		}
	}
	if (_musicData)
	{
		_musicData->play();
	}
}
