#include <wx/wx.h>
#include "ShuttingYardAlgorithm.h"

class Gui : public wxFrame
{
public:
	Gui(const wxString& title);
	
private:
	void OnButtonEvent(wxCommandEvent & event);
	void OnChoice(wxCommandEvent & event);
	unsigned n;
	wxBoxSizer *sizer;
	wxGridSizer *gs;
	wxTextCtrl *display;
	TdoubleList memory;
	string output;
	ShuttingYardAlgorithm calculate;
	bool mode;
};

const int ID_PLUS = 101;
const int ID_MINUS = 102;
const int ID_DIV = 103;
const int ID_MULT = 104;
const int ID_EQUAL = 105;
const int ID_FOWARD = 106;
const int ID_BACK = 107;
const int ID_CLEAR = 108;
const int ID_MEM = 109;
const int ID_SIN = 201;
const int ID_COS = 202;
const int ID_TG = 203;
const int ID_CTG = 204;
const int ID_ONE = 205;
const int ID_TWO = 206;
const int ID_THREE = 207;
const int ID_FOUR = 208;
const int ID_FIVE = 209;
const int ID_SIX = 301;
const int ID_SEVEN = 302;
const int ID_EIGHT = 303;
const int ID_NINE = 304;
const int ID_ZERO = 305;
const int ID_DOT = 306;
const int ID_LN = 307;
const int ID_SQRT = 308;
const int ID_SIL = 309;
const int ID_POT = 401;
const int ID_LBRACER = 402;
const int ID_RBRACER = 403;
const int ID_LOG = 404;
const int ID_RAD = 405;
const int ID_PI = 406;
const int ID_EXP = 407;
const int ID_DEG = 408;