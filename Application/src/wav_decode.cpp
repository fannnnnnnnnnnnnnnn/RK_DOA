#include"wav_decode.hpp"
#include"iostream"


using namespace std;

wav_decode::wav_decode()
{
        wave1234p.ch1.resize(RANGE);
        wave1234p.ch2.resize(RANGE);
        wave1234p.ch3.resize(RANGE);
        wave1234p.ch4.resize(RANGE);

        wav_path = "sound_data/test.wav";
        wav_start_point = 0;
}
void wav_decode::record()
{
    string cmd = "arecord -D hw:0,0 -c 8 -r 44100 -s " + to_string(RANGE)+ "  -f  S16_LE  --period-size=1024  --buffer-size=4096 /CHEVY_FYP/sound_data/test.wav &>a.log";
	system(cmd.data());
}
void wav_decode::read_wav_file()
{
    FILE *fp;
    fp = fopen(wav_path.data(), "rb");
    if(!fp)
    {
        cout << "can't open audio file\n";
    }
    fread(&wav, 1, sizeof(wav), fp);
    fclose(fp);
}
Wave1234* wav_decode::wave_to_chs(bool show_decoded_data)
{
    
    for (int i =wav_start_point * 8; i < RANGE * 8 +wav_start_point * 8; i++)

    {
        if (((i % 8 + 1) == 1) && (show_decoded_data))
        {

            cout << "###line";
            cout.width(2);
            cout << i / 8 -wav_start_point << "####|||";
        }
        if ((i == 0) && (show_decoded_data))
        {
            printf("|");
        }

        int16_t show = wav.data.block[i];
        // int16_t show = (wav.data.block[i] >> 8) | (wav.data.block[i] << 8);

        
        if ((i % 8 + 1) == 1)
        {
            wave1234p.ch1[i / 8 -wav_start_point] = show;
        }
        if ((i % 8 + 1) == 2)
        {
            wave1234p.ch2[i / 8 -wav_start_point] = show;
        }
        if ((i % 8 + 1) == 3)
        {
            wave1234p.ch3[i / 8 -wav_start_point] = show;
        }
        if ((i % 8 + 1) == 4)
        {
            wave1234p.ch4[i / 8 -wav_start_point] = show;
        }
        if (((i % 8 + 1) < 5) && (show_decoded_data))
        {
            printf("ch%d:", i % 8 + 1);
            printf("%6d", show);
            printf("|  |");
        }

        if (((i % 8 + 1) == 8) && (show_decoded_data))
        {
            printf("\n");
        }
    }
    return &wave1234p;
}
void wav_decode::set_start_point(int set_value)
{
    wav_start_point = set_value;
}
void wav_decode::set_wav_path(char* path)
{
    wav_path.assign(path);
}