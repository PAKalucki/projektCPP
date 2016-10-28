#include "gui.h"
#include "wx/wxprec.h"

Gui::Gui(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(320, 220), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	n = 0;
	
	mode = true;

	sizer = new wxBoxSizer(wxVERTICAL);

	display = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1),wxSize(-1, -1), wxTE_RIGHT);

	const wxString choice[] = { "rad", "deg" };

	sizer->Add(display, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);
	gs = new wxGridSizer(5, 7, 3, 3);

	//1 rzad
	gs->Add(new wxButton(this, ID_CLEAR, wxT("Clear")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_BACK, wxT("<-")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_FOWARD, wxT("->")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_MEM, wxT("CLM")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_SIN, wxT("sin")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_LN, wxT("ln")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_LOG, wxT("log")), 0, wxEXPAND);
	//2 rzad
	gs->Add(new wxButton(this, ID_SEVEN, wxT("7")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_EIGHT, wxT("8")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_NINE, wxT("9")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_DIV, wxT("/")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_COS, wxT("cos")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_LBRACER, wxT("(")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_PI, wxT("\u03C0")), 0, wxEXPAND);//PI
	//3 rzad
	gs->Add(new wxButton(this, ID_FOUR, wxT("4")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_FIVE, wxT("5")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_SIX, wxT("6")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_MULT, wxT("*")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_TG, wxT("tg")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_RBRACER, wxT(")")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_EXP, wxT("exp")), 0, wxEXPAND);
	//4 rzad
	gs->Add(new wxButton(this, ID_ONE, wxT("1")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_TWO, wxT("2")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_THREE, wxT("3")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_MINUS, wxT("-")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_CTG, wxT("ctg")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_POT, wxT("^")), 0, wxEXPAND);
	gs->Add(new wxChoice(this, wxID_ANY, wxDefaultPosition, wxSize(45,-1), 2, choice));
	// 5 rzad
	gs->Add(new wxButton(this, ID_ZERO, wxT("0")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_DOT, wxT(".")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_EQUAL, wxT("=")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_PLUS, wxT("+")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_SIL, wxT("!")), 0, wxEXPAND);
	gs->Add(new wxButton(this, ID_SQRT, wxT("sqrt")), 0, wxEXPAND);
	gs->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND);

	Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Gui::OnButtonEvent));
	Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(Gui::OnChoice));

	sizer->Add(gs, 1, wxEXPAND);
	SetSizer(sizer);
	SetMinSize(wxSize(320, 220));
	Centre();
}


void Gui::OnButtonEvent(wxCommandEvent& event)
{
	wxButton *button = (wxButton*)event.GetEventObject();
	int id = button->GetId();
	unsigned *wsk = &n;
	TlistElement * p;
	p = new TlistElement;

	switch (id)
	{
	case ID_ONE:
			display->AppendText("1");
			break;

	case ID_TWO:
			display->AppendText("2");
			break;

	case ID_THREE:
			display->AppendText("3");
			break;

	case ID_FOUR:
			display->AppendText("4");
			break;

	case ID_FIVE:
			display->AppendText("5");
			break;

	case ID_SIX:
			display->AppendText("6");
			break;

	case ID_SEVEN:
			display->AppendText("7");
			break;

	case ID_EIGHT:
			display->AppendText("8");
			break;

	case ID_NINE:
			display->AppendText("9");
			break;

	case ID_ZERO:
			display->AppendText("0");
			break;

	case ID_CLEAR:
			display->Clear();
			break;

	case ID_PLUS:
			display->AppendText("+");
			break;

	case ID_MINUS:
			display->AppendText("-");
			break;

	case ID_DIV:
			display->AppendText("/");
			break;

	case ID_MULT:
			display->AppendText("*");
			break;

	case ID_POT:
			display->AppendText("^");
			break;

	case ID_SQRT:
			display->AppendText("sqrt()");
			break;

	case ID_LBRACER:
			display->AppendText("(");
			break;

	case ID_RBRACER:
			display->AppendText(")");
			break;

	case ID_SIN:
			display->AppendText("sin()");
			break;

	case ID_COS:
			display->AppendText("cos()");
			break;

	case ID_TG:
			display->AppendText("tg()");
			break;

	case ID_CTG:
			display->AppendText("ctg()");
			break;

	case ID_SIL:
			display->AppendText("!");
			break;

	case ID_DOT:
			display->AppendText(".");
			break;

	case ID_LN:
			display->AppendText("ln()");
			break;

	case ID_LOG:
			display->AppendText("log()");
			break;

	case ID_MEM:
		{
			while (memory.size() != 0)
				memory.pop_front();
			display->Clear();
			display->AppendText("Pamiec wyczyszczona");
			break;
		}
	case ID_EQUAL:
		{
			wxString content = display->GetValue();
			output = string(content.mb_str());
			

			if (!(display->IsEmpty()))
			{
				p = new TlistElement;
				p->key = output;
				memory.push_front(p);
				try
				{
					if (calculate.GenerateRPN(output).empty())
					{
						display->SetValue("Error");
					}
					else
					{
						wxString mystring0(calculate.Evaluation(calculate.GenerateRPN(output), mode));
						display->SetValue(mystring0);
					}
				}
				catch (...)
				{
					display->SetValue("Error");
				}
			}
			break;
		}
	case ID_FOWARD:
		{
			
			if (*wsk > 1)
			{
				*wsk -= 1;
				p = memory.index(n);
				string wynikf = p->key;
				wxString mystring1(wynikf);
				display->SetValue(mystring1);
			}
			break;
		}
	case ID_BACK:
		{
			
			if (*wsk < memory.size())
			{
				*wsk += 1;
				p = memory.index(n);
				string wynikp = p->key;
				wxString mystring2(wynikp);
				display->SetValue(mystring2);
			}
			break;
		}

	case ID_PI:
		display->AppendText("3.14159265358979323846");
		break;

	case ID_EXP:
		display->AppendText("exp()");
		break;
	}

}

void Gui::OnChoice(wxCommandEvent & event)
{
	int i = event.GetSelection();

	switch (i)
	{
	case 0:
		mode = true;
		break;
	case 1:
		mode = false;
		break;
	}

}