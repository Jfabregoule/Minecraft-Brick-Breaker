#pragma once
#include <string>
#include <vector>

class Map
{
private:

    // Main Attributes

    int                m_sizeX;
    int                m_sizeY;
    int                m_num;
    int                m_ball;
    const    char*     m_error;

public:

    std::vector<std::string>* m_vstr;
    std::string*              m_config;
    std::string*              m_ballconfig;

    Map();
    ~Map();

private:

    // Check Methods

    bool		    IsBallNumFormated();
    bool		    IsBallNumValid();
    bool            IsConfigFormated();
    bool            IsLineFormated(std::string* line);
    bool            IsHeightFormated();
    bool            IsMapFormated();

    void            GetSize();

public:

    // Main Methods

    void            ParseMap(std::string* filePath);
    void            CheckMap();

    // Get Methods

    int                GetWidth();
    int                GetHeight();
    int                GetBall();
};