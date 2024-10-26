#include <vector>
#include <wx/wx.h>
#include <cmath>

using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
    // Verificação de limites
    if (u < 6 && v < 6 && u >= 0 && v >= 0) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

class GraphPanel : public wxPanel
{
public:
    GraphPanel(wxWindow *parent, vector<int> adj[], int n) : wxPanel(parent), n(n)
    {
        // Criar uma cópia do vetor de adjacência
        this->adj = new vector<int>[n];
        for (int i = 0; i < n; i++) {
            this->adj[i] = adj[i]; // Cópia dos dados
        }

        Bind(wxEVT_PAINT, &GraphPanel::OnPaint, this);
    }

    ~GraphPanel() {
        delete[] adj; // Libere a memória
    }

private:
    vector<int>* adj;
    int n;

    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);

        vector<wxPoint> node_positions(n);
        int radius = 100;
        int centerX = 200;
        int centerY = 200;

        for (int i = 0; i < n; i++)
        {
            double angle = 2.0 * M_PI * i / n;
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);
            node_positions[i] = wxPoint(x, y);
        }

        dc.SetPen(wxPen(*wxBLACK, 2));
        for (int i = 0; i < n; i++)
        {
            for (int neighbor : adj[i])
            {
                dc.DrawLine(node_positions[i], node_positions[neighbor]);
            }
        }

        dc.SetBrush(*wxBLUE_BRUSH);
        for (int i = 0; i < n; i++)
        {
            dc.DrawCircle(node_positions[i], 10);
            dc.DrawText(wxString::Format("%d", i), node_positions[i].x - 5, node_positions[i].y - 5);
        }
    }
};

class GraphFrame : public wxFrame
{
public:
    GraphFrame(const wxString &title, vector<int> adj[], int n)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400))
    {
        new GraphPanel(this, adj, n);
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
