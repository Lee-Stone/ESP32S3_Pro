#include "music.h"
#include <driver/i2s.h>
#include <Audio.h>
#include <SD.h>
#include "ui/src/ui.h"

#define I2S_DOUT      40
#define I2S_BCLK      41
#define I2S_LRC       42

Audio audio;

void music_init() 
{
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(16); // 0...21
    audio.setBalance(100);
    music_read();
}

void music_read()
{
    File root = SD.open("/");
    File file = root.openNextFile();
    while (file)
    {
        static int cnt = 0;
        if(cnt <= 1)cnt++;
        if (!file.isDirectory())
        {
            const char *filename = file.name();
            int8_t len = strlen(filename);
            const char *mp3_ext = ".mp3";
            if ((filename[0] != '.') && (strcmp(mp3_ext, &filename[len - 4]) == 0))
            {
                if(cnt == 1)
                {
                    memset(Music.song_name, 0, sizeof(Music.song_name));
                    strcpy(Music.song_name, filename);
                }
                Music.song_list += filename; 
                Music.song_list += "\n";
            }
        }
        file = root.openNextFile();
    }
    Music.song_options = Music.song_list.c_str();
}

void music_update()
{
    audio.loop();
    audio.setVolume(Music.volume_value); 
    if(Music.play_flag == 1)
    {
        // 暂停->播放
        if(Music.pause_flag && !audio.isRunning())
        {
            lv_label_set_text_fmt(ui_LabelMusicName, "正在播放: %s", Music.song_name);
            audio.pauseResume();
            Music.pause_flag = 0;
        }
        // 切歌
        if(Music.start_flag)
        {
            if(Game.game2048_flag == 1)
            {
                audio.connecttoFS(SD, "哈基米起床-哈基米.mp3");
            }
            else if(Game.yang_flag == 1)
            {
                audio.connecttoFS(SD, "普通Disco-羊了个羊.mp3");
            }
            else if(Game.xiaoxiaole_flag == 1)
            {
                audio.connecttoFS(SD, "123我哈你-哈基米.mp3");
            }
            else if(Game.pvz_flag == 1)
            {
                audio.connecttoFS(SD, "植物大战僵尸-背景乐.mp3");
            }
            else if(Xiaozhi.answer_flag == 1)
            {
                audio.connecttohost(Xiaozhi.answer_url.c_str());
                Music.play_flag = 0;
            }
            else 
            {
                audio.connecttoFS(SD, Music.song_name);
            }
            Music.start_flag = 0;
        }
        if(!audio.isRunning() && Music.start_flag == 0)
        {
            if(Music.play_mode == 0) // 单曲循环
            {
                // do nothing
            }
            else if(Music.play_mode == 1) // 列表循环
            {
                if(Music.play_index == lv_roller_get_option_cnt(ui_RollerMusic) - 2)
                    Music.play_index = 0;
                else 
                    Music.play_index++; 
            }
            else if(Music.play_mode == 2) // 随机播放
            {
                Music.play_index = random(0, lv_roller_get_option_cnt(ui_RollerMusic) - 2);
            }
            lv_obj_add_state(ui_StartMusic, LV_STATE_CHECKED);
            lv_roller_set_selected(ui_RollerMusic, Music.play_index, LV_ANIM_OFF);
            lv_roller_get_selected_str(ui_RollerMusic, Music.song_name, sizeof(Music.song_name));
            lv_label_set_text_fmt(ui_LabelMusicName, "正在播放: %s", Music.song_name);

			Music.start_flag = 1; 
        }
    }
    else 
    {
        // 播放->暂停
        if(!Music.pause_flag && audio.isRunning() && Xiaozhi.answer_flag == 0)
        {
            lv_label_set_text_fmt(ui_LabelMusicName, "暂停播放: %s", Music.song_name);
            audio.pauseResume();
            Music.pause_flag = 1;
        }
        else if(!audio.isRunning() && Xiaozhi.answer_flag == 1)
        {
            Xiaozhi.answer_flag = 0;
        }
    }
}


// // optional
// void audio_info(const char *info){
//     Serial.print("info        "); Serial.println(info);
// }
// void audio_id3data(const char *info){  //id3 metadata
//     Serial.print("id3data     ");Serial.println(info);
// }
// void audio_eof_mp3(const char *info){  //end of file
//     Serial.print("eof_mp3     ");Serial.println(info);
// }
// void audio_showstation(const char *info){
//     Serial.print("station     ");Serial.println(info);
// }
// void audio_showstreamtitle(const char *info){
//     Serial.print("streamtitle ");Serial.println(info);
// }
// void audio_bitrate(const char *info){
//     Serial.print("bitrate     ");Serial.println(info);
// }
// void audio_commercial(const char *info){  //duration in sec
//     Serial.print("commercial  ");Serial.println(info);
// }
// void audio_icyurl(const char *info){  //homepage
//     Serial.print("icyurl      ");Serial.println(info);
// }
// void audio_lasthost(const char *info){  //stream URL played
//     Serial.print("lasthost    ");Serial.println(info);
// }