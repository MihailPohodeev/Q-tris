#include <SFML/Graphics.hpp>
#include <mutex>

#include "json.hpp"
#include "NetworkPlayer.hxx"
#include "Figures/Element.hxx"

using json = nlohmann::json;

NetworkPlayer::NetworkPlayer(I32 id) : PlayerObject(), _userID(id), _nextFigureIndex(0) {}

void NetworkPlayer::update()
{
	return;
}

void NetworkPlayer::exchange_data()
{
	json dataFrameJSON;
	if (_dataFrameString == "")
		return;
	try
	{
		dataFrameJSON = json::parse(_dataFrameString);
		_score = dataFrameJSON.at("Score");
		_level = dataFrameJSON.at("Level");
		_lines = dataFrameJSON.at("Lines");
		_nextFigureIndex = dataFrameJSON.at("NextFigure");
		if (_nextFigureIndex < 0 || _nextFigureIndex > 6)
		{
			std::cerr << "Next figure is invalid : " << (U32)_nextFigureIndex << '\n';
			exit(-1);
		}
		Matrix resultMatrix;
		json dataArray = dataFrameJSON.at("Data");
		for (const auto& elem : dataArray)
		{
			struct ElementData tempElem;
			json color = elem.at("Col");
			tempElem.color = sf::Color(color.at("R"), color.at("G"), color.at("B"));
			json pos = elem.at("Pos");
			tempElem.position = sf::Vector2i(pos.at("X"), pos.at("Y"));
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
	catch (const std::exception& e)
	{
		std::cerr << "Network Player can't handle _dataFrameString ; Какая-то хуйня левая ваще! String : " << _dataFrameString << '\n';
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

// get next index of figure.
U8 NetworkPlayer::get_next_figure_index()
{
	return _nextFigureIndex;
}