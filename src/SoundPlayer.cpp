#include "SoundPlayer.h"
#include "SoundModule.h"

SoundPlayer::SoundPlayer()
{
    mutex_init(&_mutex);
}

std::string SoundPlayer::logPrefix()
{
    return "SoundPlayer";
}

void SoundPlayer::restorePower()
{
    _powerSave = false;
}

void SoundPlayer::savePower()
{
    _powerSave = true;
    stop();
}

void SoundPlayer::powerOn()
{
#ifdef PLAYER_POWER_PIN
    logTraceP("poweron player");
    digitalWrite(PLAYER_POWER_PIN, HIGH);
#endif
}

void SoundPlayer::powerOff()
{
#ifdef PLAYER_POWER_PIN
    logTraceP("poweroff player");
    digitalWrite(PLAYER_POWER_PIN, LOW);
#endif
}

void SoundPlayer::setup()
{
#ifdef PLAYER_POWER_PIN
    pinMode(PLAYER_POWER_PIN, OUTPUT);
    powerOn();
#endif
}

void SoundPlayer::processDuration()
{
    if (_stopping) return;
    if (_currentPlay.duration == 0) return;
    if (_currentPlay.playingMillis == 0) return;
    if (!delayCheck(_currentPlay.playingMillis, _currentPlay.duration)) return;

    logTraceP("processDuration %i/%i/%i", millis(), _currentPlay.playingMillis, _currentPlay.duration);
    logIndentUp();
    stop();
    logIndentDown();
}

void SoundPlayer::stop()
{
    if (!_playing) return;
    if (_stopping) return;
    logTraceP("stop");
    _stopping = true;
}

void SoundPlayer::play(uint16_t file, uint8_t volume, uint32_t repeats, uint32_t duration)
{
    if (_powerSave)
    {
        logTraceP("no play - powerSave mode");
        soundModule.stopped();
        return;
    }

    mutex_enter_blocking(&_mutex);
    logTraceP("play %i/%i/%i/%i", file, volume, repeats, duration);

    _nextPlay.file = file;
    _nextPlay.volume = volume;
    _nextPlay.duration = duration;
    _nextPlay.repeats = repeats;
    _nextPlay.playMillis = millis();
    mutex_exit(&_mutex);

    if (_playing) stop();
}

void SoundPlayer::processStatusStopped()
{
    // Already Stopped
    if (!_playing) return;

#ifdef INFO1_LED_PIN
    openknx.info1Led.off();
#endif

    logTraceP("processStatusStopped (%ims)", (millis() - _currentPlay.playingMillis));

    _playing = false;
    _stopping = false;
    _currentPlay = SoundPlayer::Play();

    if (_nextPlay.file == 0) soundModule.stopped();
}

void SoundPlayer::processStatusPlaying()
{
    // Already Playing
    if (_playing) return;

#ifdef INFO1_LED_PIN
    openknx.info1Led.on();
#endif

    logTraceP("processStatusPlaying (%ims)", (millis() - _currentPlay.playMillis));

    _playing = true;
    _currentPlay.playingMillis = millis();
}

void SoundPlayer::processNextPlay()
{
    // Already playing
    if (_playing) return;

    // No next play
    if (_nextPlay.file == 0) return;

    mutex_enter_blocking(&_mutex);
    logTraceP("processNextPlay %i (%i)", _nextPlay.file, (millis() - _nextPlay.playMillis));
    logIndentUp();
    playNextPlay();
    logIndentDown();

    _currentPlay = _nextPlay;
    _nextPlay = SoundPlayer::Play();
    mutex_exit(&_mutex);
}

void SoundPlayer::processStopping()
{
    if (!_playing) return;
    if (!_stopping) return;

    logTraceP("processStopping");
    _stopping = false;

    stopCurrentPlay();
}
void SoundPlayer::processCheckCurrentPlay(uint16_t delay)
{
    if (!_playing && _currentPlay.file > 0 && delayCheck(_currentPlay.playMillis, delay))
    {
        logErrorP("playback could not be started. file probably not found");
        logIndentUp();
        soundModule.stopped();
        logIndentDown();
        _currentPlay = SoundPlayer::Play();
    }
}