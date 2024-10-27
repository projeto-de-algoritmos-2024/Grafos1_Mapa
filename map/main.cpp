#include <vector>
#include <wx/wx.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
    // Verificação de limites
    if (u < 6 && v < 6 && u >= 0 && v >= 0)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

class GraphPanel : public wxPanel
{
public:
    GraphPanel(wxWindow *parent, vector<int> adj[], int n) : wxPanel(parent), n(n), node_colors(n, *wxBLUE), node_positions(n)
    {
        // Cria uma cópia do vetor de adjacência
        this->adj = new vector<int>[n];
        for (int i = 0; i < n; i++)
        {
            this->adj[i] = adj[i]; // Cópia dos dados
        }

        Bind(wxEVT_PAINT, &GraphPanel::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &GraphPanel::OnClick, this);
        Bind(wxEVT_SIZE, &GraphPanel::OnResize, this);
    }

    ~GraphPanel()
    {
        delete[] adj; // Libera a memória
    }

    void RecalculateNodePositions()
    {
        InitializeNodePositions();
        Refresh();
    }

private:
    vector<int> *adj;
    int n;
    vector<wxColor> node_colors;
    vector<wxPoint> node_positions;
    int panel_width, panel_height;

    void InitializeNodePositions()
    {
        int min_distance = 30;

        int minX = min_distance;
        int maxX = panel_width - min_distance;
        int minY = min_distance;
        int maxY = panel_height - min_distance;

        // Inicializa a semente do rand() com o tempo atual
        srand(time(0));

        for (int i = 0; i < n; i++)
        {
            bool valid_position;
            do
            {
                valid_position = true;
                int x = minX + rand() % (maxX - minX + 1);
                int y = minY + rand() % (maxY - minY + 1);
                wxPoint new_position(x, y);

                for (int j = 0; j < i; j++)
                {
                    if (sqrt(pow(new_position.x - node_positions[j].x, 2) +
                             pow(new_position.y - node_positions[j].y, 2)) < min_distance)
                    {
                        valid_position = false;
                        break;
                    }
                }

                if (valid_position)
                {
                    node_positions[i] = new_position;
                }
            } while (!valid_position);
        }
    }

    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);

        // Desenha as arestas
        dc.SetPen(wxPen(*wxBLACK, 2));
        for (int i = 0; i < n; i++)
        {
            for (int neighbor : adj[i])
            {
                dc.DrawLine(node_positions[i], node_positions[neighbor]);
            }
        }

        // Desenha os nós
        for (int i = 0; i < n; i++)
        {
            dc.SetBrush(wxBrush(node_colors[i]));
            dc.DrawCircle(node_positions[i], 16);
            dc.DrawText(wxString::Format("%d", i), node_positions[i].x - 8, node_positions[i].y - 8);
        }
    }

    void OnClick(wxMouseEvent &event)
    {
        wxPoint click_pos = event.GetPosition();
        int node_radius = 16;

        for (int i = 0; i < n; i++)
        {
            // Verifica se o clique está dentro do raio do nó
            if (click_pos.x >= node_positions[i].x - node_radius && click_pos.x <= node_positions[i].x + node_radius &&
                click_pos.y >= node_positions[i].y - node_radius && click_pos.y <= node_positions[i].y + node_radius)
            {
                // Altera a cor do nó clicado
                node_colors[i] = (node_colors[i] == *wxBLUE) ? *wxRED : *wxBLUE;
                Refresh(); // Redesenha o painel para aplicar a mudança de cor
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
    GraphFrame(const wxString &title, vector<int> adj[], int n)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 800))
    {
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        panel = new GraphPanel(this, adj, n);
        sizer->Add(panel, 1, wxEXPAND);

        wxButton *button = new wxButton(this, wxID_ANY, "Refresh");
        sizer->Add(button, 0, wxALIGN_LEFT | wxALL, 10);

        SetSizer(sizer);

        button->Bind(wxEVT_BUTTON, &GraphFrame::OnRefresh, this);
    }

private:
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
        vector<int> adj[6];
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 1, 3);
        addEdge(adj, 1, 4);
        addEdge(adj, 2, 5);

        GraphFrame *frame = new GraphFrame("Graph Visualization", adj, 6);
        frame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
