#include <SFML/Graphics.hpp>
#include <mutex>

#include "json.hpp"
#include "NetworkPlayer.hxx"
#include "Figures/Element.hxx"

using json = nlohmann::json;

NetworkPlayer::NetworkPlayer(I32 id) : PlayerObject(), _userID(id) {}

void NetworkPlayer::update()
{
	return;
}

void NetworkPlayer::exchange_data()
{
	json dataFrameJSON;
	try
	{
		dataFrameJSON = json::parse(_dataFrameString);
		Matrix resultMatrix;
		for (const auto& elem : dataFrameJSON)
		{
			struct ElementData tempElem;
			json color = elem["Color"];
			tempElem.color = sf::Color(color["R"], color["G"], color["B"]);
			json pos = elem["Position"];
			tempElem.position = sf::Vector2i(pos["X"], pos["Y"]);
			resultMatrix.add_element(tempElem);
		}
		 if (!_doubleFrame)
		 {
			 std::cerr << "NetworkPlayer error : _doubleFrame object is null!!!\nNetPlayer_ID : " << _userID << '\n';
			 exit(-1);
		 }
		 _doubleFrame->set_matrix(resultMatrix);
		 _doubleFrame->swap_buffers();
	}
	catch(const json::parse_error& e)
	{
		std::cerr << "Network Player can't handle _dataFrameString ; Parse error at byte : " << e.byte << " : " << e.what() << " ; String : " << _dataFrameString << '\n';
	}
	catch (const json::type_error& e)
	{
		std::cerr << "Network Player can't handle _dataFrameString ; Type error : " << e.what() << " ; String : " << _dataFrameString << '\n';
	}
	catch (const json::out_of_range& e)
	{
		std::cerr << "Network Player can't handle _dataFrameString  ; Out of range error : " << e.what() << " ; String : " << _dataFrameString << '\n';
	}
}

// get id.
I32 NetworkPlayer::get_ID() const
{
	return _userID;
}

// set id.
void NetworkPlayer::set_ID(I32 id)
{
	_userID = id;
}

// get username.
std::string NetworkPlayer::get_username() const
{
	return _username;
}

// set username.
void NetworkPlayer::set_username(const std::string& username)
{
	_username = username;
}

// set data frame string.
void NetworkPlayer::set_data_frame_string(const std::string& str)
{
	_dataFrameString = str;
}
