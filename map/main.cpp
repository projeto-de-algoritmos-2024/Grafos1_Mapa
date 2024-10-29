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
    vector<int> selected_nodes;
    int panel_width, panel_height;

    void InitializeNodePositions()
    {
    int grid_size = ceil(sqrt(n)); // Define o tamanho da grade baseado na raiz quadrada do número de nós
    int padding = 50; // Espaçamento entre os nós e as bordas do painel
    int cell_width = (panel_width - 2 * padding) / grid_size;
    int cell_height = (panel_height - 2 * padding) / grid_size;

        for (int i = 0; i < n; i++)
        {
        int row = i / grid_size;
        int col = i % grid_size;

        int x = padding + col * cell_width + cell_width / 2;
        int y = padding + row * cell_height + cell_height / 2;

        node_positions[i] = wxPoint(x, y);
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
                if (find(selected_nodes.begin(), selected_nodes.end(), i) == selected_nodes.end())
                {
                    if (selected_nodes.size() < 2)
                    {
                        selected_nodes.push_back(i);
                        node_colors[i] = *wxRED;
                    }
                    else
                    {
                        int first_selected = selected_nodes.front();
                        node_colors[first_selected] = *wxBLUE;
                        selected_nodes.erase(selected_nodes.begin());
                        selected_nodes.push_back(i);
                        node_colors[i] = *wxRED;
                    }
                }
                else
                {
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
