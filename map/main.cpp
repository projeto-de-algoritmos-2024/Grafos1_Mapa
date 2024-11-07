#include "graph.h"
#include <vector>
#include <wx/wx.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

class GraphPanel : public wxPanel
{
public:
    GraphPanel(wxWindow *parent, Graph *graph) : wxPanel(parent), graph(graph), n(graph->getSize()), node_colors(n, *wxBLUE), node_positions(n)
    {
        Bind(wxEVT_PAINT, &GraphPanel::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &GraphPanel::OnClick, this);
        Bind(wxEVT_SIZE, &GraphPanel::OnResize, this);
    }
    
    void RecalculateNodePositions()
    {
        InitializeNodePositions();
        Refresh();
    }

private:
    Graph *graph;
    int n;
    vector<wxColor> node_colors;
    vector<wxPoint> node_positions;
    vector<int> selected_nodes;
    int panel_width, panel_height;
    // vector<string> disciplines = {"Calculo 1", "APC", "DIAC", "Eng e Amb", "Intro a Eng", "Calculo 2", "Fisica 1", "Fisica Exp", "IAL", "PE", "DS", "MN", "Eng Econ", "HC", "TED", "PED", "OO", "MD1", "GPeQ", "MDS", "EDA1", "FAC", "MD2", "PI1", "IHC", "Requisitos", "SBD1", "FSO", "Compiladores", "EDA2", "QSW", "TSW", "Arq e Des", "Redes", "SBD2", "PA", "TPPE", "Paradigmas", "FSE", "PSPD", "EPS", "GCES", "Estagio", "TCC1", "PI2", "TCC2"};
    vector<vector<string>> disciplines = {
    {"Calculo 1", "APC", "DIAC", "Eng e Amb", "Intro a Eng"},
    {"Calculo 2", "Fisica 1", "Fisica Exp", "IAL", "PE", "DS"},
    {"MN", "Eng Econ", "HC", "TED", "PED", "OO", "MD1"},
    {"GPeQ", "MDS", "EDA1", "FAC", "MD2", "PI1"},
    {"IHC", "Requisitos", "SBD1", "FSO", "Compiladores", "EDA2"},
    {"QSW", "TSW", "Arq e Des", "Redes", "SBD2", "PA"},
    {"TPPE", "Paradigmas", "FSE", "PSPD"},
    {"EPS", "GCES", "Estagio"}, 
    {"TCC1", "PI2"},
    {"TCC2"}
};

    void InitializeNodePositions()
    {
        int padding = 50;              // Espaçamento entre as bordas do painel e os nós
        int layer_spacing = 150;       // Espaço horizontal entre cada camada (semestre)
        int node_spacing = 80;         // Espaço vertical entre cada nó na camada

        int x_position = padding;      // Inicia a primeira camada na borda esquerda do painel

        for (int semester = 0; semester < disciplines.size(); semester++)
        {
            int y_position = padding;  // Inicia a camada no topo do painel

            // Para cada disciplina no semestre atual, define a posição do nó
            for (int node_index = 0; node_index < disciplines[semester].size(); node_index++)
            {
                int index = 0;
                for (int i = 0; i < semester; i++) {
                    index += disciplines[i].size();
                }
                index += node_index;

                // Define a posição x e y do nó atual
                node_positions[index] = wxPoint(x_position, y_position);

                // Move y para a próxima posição na mesma camada
                y_position += node_spacing;
            }

            // Move x para a próxima camada
            x_position += layer_spacing;
        }
    }

    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);

        // Desenha as arestas 
        dc.SetPen(wxPen(*wxBLACK, 2));
        for (int i = 0; i < n; i++)
        {
            for (int neighbor : graph->getAdjList(i))
            {
                dc.DrawLine(node_positions[i], node_positions[neighbor]);
            }
        }

        // Desenha os nós
        int node_index = 0;
        for (const auto& semester : disciplines)
        {
            for (const auto& discipline : semester)
            {
                dc.SetBrush(wxBrush(node_colors[node_index]));
                dc.DrawRectangle(node_positions[node_index].x - 10, node_positions[node_index].y - 20, 90, 40);
                dc.DrawText(wxString::Format("%s", discipline), node_positions[node_index].x - 8, node_positions[node_index].y - 8);
                node_index++;
            }
        }
    }

    void OnClick(wxMouseEvent &event)
{
    wxPoint click_pos = event.GetPosition();
    int rect_width = 90;
    int rect_height = 40;

    for (int i = 0; i < n; i++)
    {
        // Verifica se o clique está dentro do retângulo do nó
        if (click_pos.x >= node_positions[i].x - 10 && click_pos.x <= node_positions[i].x - 10 + rect_width &&
            click_pos.y >= node_positions[i].y - 20 && click_pos.y <= node_positions[i].y - 20 + rect_height)
        {
            if (find(selected_nodes.begin(), selected_nodes.end(), i) == selected_nodes.end())
            {
                // Seleciona o nó, marca como vermelho e adiciona à lista de nós selecionados
                selected_nodes.push_back(i);
                node_colors[i] = *wxRED;
            }
            else
            {
                // Deseleciona o nó, marca como azul e remove da lista de nós selecionados
                node_colors[i] = *wxBLUE;
                selected_nodes.erase(remove(selected_nodes.begin(), selected_nodes.end(), i), selected_nodes.end());
            }
            Refresh();
            break;
        }
    }
}

    void OnResize(wxSizeEvent &event)
    {
        wxSize panelSize = GetClientSize();
        panel_width = panelSize.GetWidth();
        panel_height = panelSize.GetHeight();

        InitializeNodePositions();
        Refresh();    // Redesenha o painel após redimensionar
        event.Skip(); // Permite que o evento seja processado por outros manipuladores, se houver
    }
};

class GraphFrame : public wxFrame
{
public:
    GraphFrame(const wxString &title, Graph *graph)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1500, 700))
    {
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        panel = new GraphPanel(this, graph);
        sizer->Add(panel, 1, wxEXPAND);

        wxButton *button = new wxButton(this, wxID_ANY, "Refresh");
        sizer->Add(button, 0, wxALIGN_LEFT | wxALL, 10);

        SetSizer(sizer);

        button->Bind(wxEVT_BUTTON, &GraphFrame::OnRefresh, this);
    }

private:
    Graph *graph;
    GraphPanel *panel;

    void OnRefresh(wxCommandEvent &event)
    {
        panel->RecalculateNodePositions();
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        Graph *g = new Graph(46);
        g->addEdge(0, 5);
        g->addEdge(0, 9);
        g->addEdge(0, 35);
        g->addEdge(1, 10);
        g->addEdge(1, 16);
        g->addEdge(1, 20);
        g->addEdge(2, 24);

        g->addEdge(5, 11);
        g->addEdge(8, 14);
        g->addEdge(8, 15);

        g->addEdge(12, 18);
        g->addEdge(14, 15);
        g->addEdge(14, 15);
        g->addEdge(14, 21);
        g->addEdge(16, 19);
        g->addEdge(16, 35);
        g->addEdge(16, 23);
        g->addEdge(17, 22);

        g->addEdge(18, 30);
        g->addEdge(19, 25);
        g->addEdge(19, 31);
        g->addEdge(20, 28);
        g->addEdge(20, 29);
        g->addEdge(20, 35);
        g->addEdge(21, 27);
        g->addEdge(22, 26);
        g->addEdge(23, 44);
        
        g->addEdge(24, 30);
        g->addEdge(25, 32);
        g->addEdge(26, 34);
        g->addEdge(27, 33);
        g->addEdge(27, 38);
        g->addEdge(28, 37);
        g->addEdge(29, 39);

        g->addEdge(31, 36);
        g->addEdge(31, 41);
        g->addEdge(32, 37);
        g->addEdge(33, 39);

        g->addEdge(36, 40);

        g->addEdge(40, 44);

        g->addEdge(43, 45);

        GraphFrame *frame = new GraphFrame("Graph Visualization", g);
        frame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);