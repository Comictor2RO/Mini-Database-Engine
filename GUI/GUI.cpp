#include "GUI.hpp"

#include <algorithm>

GUI::GUI(Catalog &catalog, Engine &engine)
    : catalog(catalog), engine(engine), isDark(true), cursorPos(0), backspaceRepeatTimer(0)
{}

void GUI::run()
{
    InitWindow(1280, 720, "Database Engine");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        handleInput();
        BeginDrawing();
        ClearBackground(isDark ? BLACK : WHITE);
        drawInputPanel();
        drawResultsPanel();
        drawLogPanel();
        EndDrawing();
    }
    CloseWindow();
}

void GUI::handleInput()
{
    int ch = GetCharPressed();
    while (ch > 0)
    {
        input.insert(cursorPos, 1, (char)ch);
        cursorPos++;
        ch = GetCharPressed();
    }

    if (IsKeyPressed(KEY_LEFT) && cursorPos > 0)
        cursorPos--;
    if (IsKeyPressed(KEY_RIGHT) && cursorPos < (int)input.size())
        cursorPos++;

    if (IsKeyPressed(KEY_BACKSPACE) && cursorPos > 0)
    {
        input.erase(cursorPos - 1, 1);
        cursorPos--;
        backspaceRepeatTimer = 0.5f;
    }
    if (IsKeyDown(KEY_BACKSPACE) && cursorPos > 0)
    {
        backspaceRepeatTimer -= GetFrameTime();
        if (backspaceRepeatTimer <= 0)
        {
            input.erase(cursorPos - 1, 1);
            cursorPos--;
            backspaceRepeatTimer = 0.05f;
        }
    }
    if (!IsKeyDown(KEY_BACKSPACE))
        backspaceRepeatTimer = 0;

    if (IsKeyPressed(KEY_ENTER) && !input.empty())
        executeQuery();
}

void GUI::executeQuery()
{
    logs.push_back("> " + input);
    try
    {
        results = engine.query(input);

        std::string upper = input;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        if (upper.rfind("DROP TABLE", 0) == 0)
            logs.push_back("[OK] Table dropped.");
        else if (!results.empty())
            logs.push_back("[OK] Rows returned: " + std::to_string(results.size()));
        else
            logs.push_back("[OK] Command executed.");
    }
    catch (const std::exception &e)
    {
        results.clear();
        logs.push_back("[ERROR] " + std::string(e.what()));
    }
    catch (...)
    {
        results.clear();
        logs.push_back("[ERROR] Query invalid sau tabela inexistenta.");
    }
    input.clear();
    cursorPos = 0;
}

void GUI::drawInputPanel()
{
    int width = GetRenderWidth();
    DrawRectangle(0, 0, width, 80, isDark ? DARKGRAY : LIGHTGRAY);

    Rectangle inputBox = {10, 20, 1100, 40};
    DrawRectangleRec(inputBox, isDark ? BLACK : WHITE);
    DrawRectangleLinesEx(inputBox, 1, isDark ? WHITE : DARKGRAY);
    DrawText(input.c_str(), 18, 30, 20, isDark ? WHITE : BLACK);

    bool showCursor = (int)(GetTime() * 2) % 2 == 0;
    if (showCursor)
    {
        std::string leftPart = input.substr(0, cursorPos);
        int cursorX = 18 + MeasureText(leftPart.c_str(), 20);
        DrawText("|", cursorX, 30, 20, GRAY);
    }

    Rectangle runBtn = {1120, 20, 140, 40};
    bool hover = CheckCollisionPointRec(GetMousePosition(), runBtn);
    DrawRectangleRec(runBtn, hover ? GREEN : LIME);
    DrawText("RUN", 1170, 30, 20, BLACK);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !input.empty())
        executeQuery();
}

void GUI::drawResultsPanel()
{
    Color bg     = isDark ? Color{30, 30, 30, 255}  : Color{245, 245, 245, 255};
    Color header = isDark ? Color{50, 50, 50, 255}  : Color{200, 200, 200, 255};
    Color even   = isDark ? Color{40, 40, 40, 255}  : Color{255, 255, 255, 255};
    Color odd    = isDark ? Color{55, 55, 55, 255}  : Color{230, 230, 230, 255};
    Color text   = isDark ? WHITE : BLACK;

    DrawRectangle(0, 80, 1280, 440, bg);
    DrawRectangle(0, 80, 1280, 28, header);
    DrawText("RESULTS", 10, 88, 16, isDark ? LIGHTGRAY : DARKGRAY);
    DrawText(("Total rows: " + std::to_string(results.size())).c_str(), 120, 88, 16, isDark ? LIGHTGRAY : DARKGRAY);

    if (results.empty())
    {
        DrawText("No results to display.", 10, 120, 18, GRAY);
        return;
    }

    int startY    = 115;
    int rowHeight = 26;
    int maxRows   = (440 - 35) / rowHeight;

    for (int i = 0; i < (int)results.size() && i < maxRows; i++)
    {
        int y = startY + i * rowHeight;
        DrawRectangle(0, y, 1280, rowHeight, i % 2 == 0 ? even : odd);

        std::string rowStr;
        for (int j = 0; j < (int)results[i].values.size(); j++)
        {
            if (j > 0) rowStr += "   |   ";
            rowStr += results[i].values[j];
        }
        DrawText(rowStr.c_str(), 10, y + 4, 18, text);
    }
}

void GUI::drawLogPanel()
{
    Color bg     = isDark ? Color{20, 20, 20, 255} : Color{210, 210, 210, 255};
    Color header = isDark ? DARKGRAY : GRAY;

    DrawRectangle(0, 520, 1280, 200, bg);
    DrawRectangle(0, 520, 1280, 25, header);
    DrawText("LOG", 10, 527, 15, isDark ? WHITE : BLACK);

    // Buton toggle dark/light mode
    Rectangle toggleBtn = {1190, 523, 80, 19};
    bool hover = CheckCollisionPointRec(GetMousePosition(), toggleBtn);
    DrawRectangleRec(toggleBtn, hover ? SKYBLUE : BLUE);
    DrawText(isDark ? "LIGHT" : "DARK", 1200, 527, 14, WHITE);
    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        isDark = !isDark;

    int lineHeight = 19;
    int maxLines   = (200 - 30) / lineHeight;
    int startIdx   = (int)logs.size() > maxLines ? (int)logs.size() - maxLines : 0;

    for (int i = startIdx; i < (int)logs.size(); i++)
    {
        int y = 550 + (i - startIdx) * lineHeight;
        bool isError = logs[i].find("ERROR") != std::string::npos;
        Color c = isError ? RED : (isDark ? GREEN : DARKGREEN);
        DrawText(logs[i].c_str(), 10, y, 15, c);
    }
}
