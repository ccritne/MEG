#include "lib/Button.hpp"
#include "lib/TextBox.hpp"
using namespace std;


void MEG(vector<vector<double>> &A){
    double s;
    bool dbg = false;
    int p = 0;
    int R = A.size();
    int C = A[0].size();

    while(p < R){
        bool condZero = false;
        if(A[p][p] == 0.0){
            for(int i = p+1; i < R and condZero; i++){
                if(A[i][p] != 0.0){
                    for(int j = p; j < C; j++)
                        swap(A[p][j], A[i][j]);
                    condZero = false;
                }
            }
        }else
            condZero = true;
        
        if(condZero == true){
            for(int i = p+1; i < R; i++){
                if(A[i][p] != 0.0){
                    s = -A[i][p]/A[p][p];
                    for(int j = p; j < C; j++){
                        A[i][j] = s*A[p][j] + A[i][j]; 
                    }
                }            
            }
            }

        p++;
    }
}


int main(){

    sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "MEG", sf::Style::Default, settings);
	window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("need/arial.ttf");
    
    vector<Textbox> boxs;
    vector<bool> condBoxs;
    vector<string> boxsText;
    
    vector<vector<double>> A;

    
    Textbox rows(320, 40, 30, 30, font);
    rows.setText("R:");
    
    Textbox column(370, 40, 30, 30, font);
    column.setText("C:");

    Button create(420, 40, 60, 30, font);
	create.setText("CREATE!");

    Button go(330, 760, 60, 25, font);
	go.setText("GO!");

    int R, C;

    bool update = false;

    bool condR = false;
    bool condC = false;

    string tR = "";
    string tC = "";

	while (window.isOpen()){
		sf::Event event;

		while (window.pollEvent(event)){
			
            if(event.type == sf::Event::Closed){
				window.close();
            }

            for(int i = 0; i < boxs.size(); i++){
                if(boxs[i].contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
                    fill(condBoxs.begin(), condBoxs.end(), false);
                    condBoxs[i] = true;
                }

                if(event.type == Event::TextEntered && condBoxs[i] && event.text.unicode != 8 && event.text.unicode != 13){
                    boxsText[i] += static_cast<char>(event.text.unicode);
                }

                if (event.type == Event::KeyPressed && condBoxs[i] && event.key.code == Keyboard::BackSpace && !tR.empty()){
                    boxsText[i].pop_back();
                }

            }

            if(create.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
                condR = false;
                condC = false;
                
                R=stold(tR);
                C=stold(tC);

                boxs.clear();
                condBoxs.clear();
                boxsText.clear();
                A.clear();

                int xStart = 50;
                int yStart = 110;

                int marginCeilsX = 10;
                int marginCeilsY = 10;

                int width = 700;
                int height = 610;

                double widthBox = (width-marginCeilsX*(C-1))/C;
                double heightBox = (height-marginCeilsY*(R-1))/R;

                int x = xStart;
                int y = yStart;

                vector<double> rs;
                for(int i = 0; i < R; i++){
                    x = xStart;
                    rs.clear();
                    for(int j = 0; j < C; j++){
                        Textbox tmp(x, y, widthBox, heightBox, font);
                        tmp.setCharacterSize(heightBox/4);
                        boxs.push_back(tmp);
                        condBoxs.push_back(false);
                        boxsText.push_back("");
                        rs.push_back(0);
                        x += widthBox + marginCeilsX;
                    }
                    A.push_back(rs);
                    y += heightBox + marginCeilsY;

                }
            }

            if(go.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
                int counter = 0;
                for(int i = 0; i < R; i++)
                    for(int j = 0; j < C; j++)
                        A[i][j] = stold(boxsText[counter]), counter++;
                
                MEG(A);

                counter = 0;
                for(int i = 0; i < R; i++)
                    for(int j = 0; j < C; j++){
                        boxsText[counter] = truncate(to_string(A[i][j]), 2);
                        counter++;
                    }
            }

            if(event.type == Event::TextEntered && condR && event.text.unicode != 8 && event.text.unicode != 13){
                tR += static_cast<char>(event.text.unicode);
            }

            if(event.type == Event::TextEntered && condC && event.text.unicode != 8 && event.text.unicode != 13){
                tC += static_cast<char>(event.text.unicode);
            }
            
            if(rows.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
                condR = true;
                condC = false;
            }
            
            if(column.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
                condR = false;
                condC = true;
            }
            
            if (event.type == Event::KeyPressed && condR && event.key.code == Keyboard::BackSpace && !tR.empty()){
                tR.pop_back();
                if(!tR.empty() and isNumber(tR))
                    R = stold(tR);
            }
            
            if (event.type == Event::KeyPressed && condC && event.key.code == Keyboard::BackSpace && !tC.empty()){
                tC.pop_back();
                if(!tC.empty() and isNumber(tC))
                    C = stold(tC);
            }
        }

        if(rows.getText() != tR)
                rows.setText(tR);

        if(column.getText() != tC)
            column.setText(tC);
        
        for(int i = 0; i < boxs.size(); i++){
            if(boxs[i].getText() != boxsText[i])
                boxs[i].setText(boxsText[i]);
        }

		window.clear();
        
        window.draw(rows);
        window.draw(column);
        window.draw(create);


        window.draw(go);

        for(int i = 0; i<boxs.size(); i++)
            window.draw(boxs[i]);

	    window.display();

    }

    return 0;
}