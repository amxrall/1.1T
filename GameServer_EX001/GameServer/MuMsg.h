#ifndef _MU_GET_MSG_H
#define _MU_GET_MSG_H

#define MSGGET(cat, id) ( (cat) * 256 + (id) )

class CMsg
{
public:
	CMsg();
	virtual ~CMsg();

	void Load(LPSTR filename);
	LPSTR Get(int idx);

private:
	char szDefaultMsg[50];
	std::map<int, std::string> MsgById;
	void lMsgFree();
};

#endif