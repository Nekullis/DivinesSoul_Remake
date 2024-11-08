#include "ModeEnding.h"
#include "ModeGameClear.h"
#include "ApplicationGlobal.h"
bool ModeEnding::Initialize()
{
    _handleMovie = LoadGraph("res/Movie/Ending.mp4");
    return true;
}

bool ModeEnding::Terminate()
{
    DeleteGraph(_handleMovie);
    return true;
}

bool ModeEnding::Process()
{
    //Ä¶‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î“®‰æ‚ðÄ¶‚·‚é
    if (GetMovieStateToGraph(_handleMovie) == 0 && TellMovieToGraph(_handleMovie) == 0)
    {
        PlayMovieToGraph(_handleMovie);
        ChangeMovieVolumeToGraph(150, _handleMovie);
    }
    if (GetMovieStateToGraph(_handleMovie) == 0)
    {
        // ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
        ModeServer::GetInstance()->Del(this);
        // ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
        ModeServer::GetInstance()->Add(new ModeClear(), 1, "clear");
    }
    return true;
}

bool ModeEnding::Render()
{
    DrawGraph(0, 0, _handleMovie, FALSE);
    return true;
}
