//
// Created by Sam on 08/12/2020.
//

#include "sha256.h"
#include "GEAH_Compressor.h"

bool GEAH_Compressor::isValid()
{
	// thanks 7-zip for the hash
	std::string sha256Str = "360f2af2e1e143045b5602f71fc4a1d69b69db3794f9fd61733bb757f573ac1c";

	std::ifstream file("geah.txt", std::ios::binary);
	std::vector<unsigned char> s(picosha2::k_digest_size);
	picosha2::hash256(file, s.begin(), s.end());
	std::string generatedHash = picosha2::bytes_to_hex_string(s.begin(),s.end());
	return generatedHash == sha256Str;
}

void findAndReplace(std::string &content, const std::string &find, const std::string &replace)
{
	size_t startPos = content.find(find); // get start position
	if(startPos==std::string::npos)return;
	content.replace(startPos,find.length(),replace); // use c++ std::string::replace
}

void GEAH_Compressor::compress(std::string fileName)
{
	if(file!=nullptr)
	{
		std::vector<std::string> backup = *file;
		auto* out = new std::vector<std::string>;
		for(int i=0;i<file->size();i++)
		{
			std::string line = file->at(i);
			bool bMadeReplacement=false;
			// I would like to apologize for the next 268 lines. I'm truly sorry
			// refer to geahMapping.txt
			// there are many occurrences of 'green eggs and ham' being followed by 'I do not like them' on the next line
			if(line.find("green eggs and ham")!=std::string::npos&&
			   file->at(i+1).find("I do not like them")!=std::string::npos)
			{
				findAndReplace(line,"green eggs and ham","1");
				findAndReplace(file->at(i+1),"I do not like them","");
				bMadeReplacement=true;
			}
			if(line.find("I do not like them")!=std::string::npos)
			{
				findAndReplace(line,"I do not like them","2");
				bMadeReplacement=true;
			}
			if(line.find("Would you like them")!=std::string::npos)
			{
				findAndReplace(line,"Would you like them","6");
				bMadeReplacement=true;
			}
			if(line.find("I would not could not")!=std::string::npos)
			{
				findAndReplace(line,"I would not could not","%");
				bMadeReplacement=true;
			}
			if(line.find("I will not eat them")!=std::string::npos)
			{
				findAndReplace(line,"I will not eat them","$");
				bMadeReplacement=true;
			}
			if(line.find("And I will eat")!=std::string::npos)
			{
				findAndReplace(line,"And I will eat","=");
				bMadeReplacement=true;
			}
			if(line.find("And I would eat")!=std::string::npos)
			{
				findAndReplace(line,"And I would eat","+");
				bMadeReplacement=true;
			}
			if(line.find("I do not like")!=std::string::npos)
			{
				findAndReplace(line,"I do not like","`");
				bMadeReplacement=true;
			}
			if(line.find("green eggs and ham")!=std::string::npos)
			{
				findAndReplace(line,"green eggs and ham","*");
				bMadeReplacement=true;
			}
			if(line.find("in the dark")!=std::string::npos)
			{
				findAndReplace(line,"in the dark","Ú");
				bMadeReplacement=true;
			}
			if(line.find("in the rain")!=std::string::npos)
			{
				findAndReplace(line,"in the rain","§");
				bMadeReplacement=true;
			}
			if(line.find("let me be")!=std::string::npos)
			{
				findAndReplace(line,"let me be","?");
				bMadeReplacement=true;
			}
			if(line.find("them Sam-I-am")!=std::string::npos)
			{
				findAndReplace(line,"them Sam-I-am","4");
				bMadeReplacement=true;
			}
			if(line.find("Would you")!=std::string::npos)
			{
				findAndReplace(line,"Would you","7");
				bMadeReplacement=true;
			}
			if(line.find("Could you")!=std::string::npos)
			{
				findAndReplace(line,"Could you","8");
				bMadeReplacement=true;
			}
			if(line.find("would you")!=std::string::npos)
			{
				findAndReplace(line,"would you","9");
				bMadeReplacement=true;
			}
			if(line.find("could you")!=std::string::npos)
			{
				findAndReplace(line,"could you","0");
				bMadeReplacement=true;
			}
			if(line.find("You may")!=std::string::npos)
			{
				findAndReplace(line,"You may","]");
				bMadeReplacement=true;
			}
			if(line.find("you may")!=std::string::npos)
			{
				findAndReplace(line,"you may","{");
				bMadeReplacement=true;
			}
			if(line.find("A train")!=std::string::npos)
			{
				findAndReplace(line,"A train","^");
				bMadeReplacement=true;
			}
			if(line.find("a train")!=std::string::npos)
			{
				findAndReplace(line,"a train","&");
				bMadeReplacement=true;
			}
			if(line.find("in a")!=std::string::npos)
			{
				findAndReplace(line,"in a","~");
				bMadeReplacement=true;
			}
			if(line.find("with a")!=std::string::npos)
			{
				findAndReplace(line,"with a","!");
				bMadeReplacement=true;
			}
			if(line.find("like them")!=std::string::npos)
			{
				findAndReplace(line,"like them","5");
				bMadeReplacement=true;
			}
			if(line.find("Thank you")!=std::string::npos)
			{
				findAndReplace(line,"Thank you","▓");
				bMadeReplacement=true;
			}
			if(line.find("green eggs")!=std::string::npos)
			{
				findAndReplace(line,"green eggs","®");
				bMadeReplacement=true;
			}
			if(line.find("I like")!=std::string::npos)
			{
				findAndReplace(line,"I like","♣");
				bMadeReplacement=true;
			}
			if(line.find("I would")!=std::string::npos)
			{
				findAndReplace(line,"I would","Ä");
				bMadeReplacement=true;
			}
			if(line.find("so good")!=std::string::npos)
			{
				findAndReplace(line,"so good","○");
				bMadeReplacement=true;
			}
			if(line.find("them")!=std::string::npos)
			{
				findAndReplace(line,"them","3");
				bMadeReplacement=true;
			}
			if(line.find("fox")!=std::string::npos)
			{
				findAndReplace(line,"fox","(");
				bMadeReplacement=true;
			}
			if(line.find("box")!=std::string::npos)
			{
				findAndReplace(line,"box",")");
				bMadeReplacement=true;
			}
			if(line.find("Eat")!=std::string::npos)
			{
				findAndReplace(line,"Eat","ô");
				bMadeReplacement=true;
			}
			if(line.find("Try")!=std::string::npos)
			{
				findAndReplace(line,"Try","ó");
				bMadeReplacement=true;
			}
			if(line.find("not")!=std::string::npos)
			{
				findAndReplace(line,"not","@");
				bMadeReplacement=true;
			}
			if(line.find("Not")!=std::string::npos)
			{
				findAndReplace(line,"Not","_");
				bMadeReplacement=true;
			}
			if(line.find("Sam-I-am")!=std::string::npos)
			{
				findAndReplace(line,"Sam-I-am","£");
				bMadeReplacement=true;
			}
			if(line.find("mouse")!=std::string::npos)
			{
				findAndReplace(line,"mouse","ƒ");
				bMadeReplacement=true;
			}
			if(line.find("house")!=std::string::npos)
			{
				findAndReplace(line,"house","ª");
				bMadeReplacement=true;
			}
			if(line.find("eat")!=std::string::npos)
			{
				findAndReplace(line,"eat",".");
				bMadeReplacement=true;
			}
			if(line.find("anywhere")!=std::string::npos)
			{
				findAndReplace(line,"anywhere",">");
				bMadeReplacement=true;
			}
			if(line.find("here")!=std::string::npos)
			{
				findAndReplace(line,"here","<");
				bMadeReplacement=true;
			}
			if(line.find("there")!=std::string::npos)
			{
				findAndReplace(line,"there","/");
				bMadeReplacement=true;
			}
			if(line.find("would")!=std::string::npos)
			{
				findAndReplace(line,"would","\\");
				bMadeReplacement=true;
			}
			if(line.find("could")!=std::string::npos)
			{
				findAndReplace(line,"could","|");
				bMadeReplacement=true;
			}
			if(line.find("goat")!=std::string::npos)
			{
				findAndReplace(line,"goat",";");
				bMadeReplacement=true;
			}
			if(line.find("boat")!=std::string::npos)
			{
				findAndReplace(line,"boat",":");
				bMadeReplacement=true;
			}
			if(line.find("Sam")!=std::string::npos)
			{
				findAndReplace(line,"Sam","\"");
				bMadeReplacement=true;
			}
			if(line.find("car")!=std::string::npos)
			{
				findAndReplace(line,"car","\'");
				bMadeReplacement=true;
			}
			if(line.find("tree")!=std::string::npos)
			{
				findAndReplace(line,"tree","[");
				bMadeReplacement=true;
			}
			if(line.find("You")!=std::string::npos)
			{
				findAndReplace(line,"You","◘");
				bMadeReplacement=true;
			}
			if(line.find("you")!=std::string::npos)
			{
				findAndReplace(line,"you","•");
				bMadeReplacement=true;
			}
			if(line.find("will")!=std::string::npos)
			{
				findAndReplace(line,"will","╚");
				bMadeReplacement=true;
			}
			if(line.find("that")!=std::string::npos)
			{
				findAndReplace(line,"that","Ì");
				bMadeReplacement=true;
			}
			if(line.find("That")!=std::string::npos)
			{
				findAndReplace(line,"That","▀");
				bMadeReplacement=true;
			}
			if(line.find("say")!=std::string::npos)
			{
				findAndReplace(line,"say","┌");
				bMadeReplacement=true;
			}
			if(line.find("like")!=std::string::npos)
			{
				findAndReplace(line,"like","î");
				bMadeReplacement=true;
			}
			if(line.find("and")!=std::string::npos)
			{
				findAndReplace(line,"and","├");
				bMadeReplacement=true;
			}
			if(line.find("And")!=std::string::npos)
			{
				findAndReplace(line,"And","¨");
				bMadeReplacement=true;
			}
			if(line.find("see")!=std::string::npos)
			{
				findAndReplace(line,"see","▄");
				bMadeReplacement=true;
			}

			if(bMadeReplacement)
			{
				file->at(i)=line;
				i--;
			}
			else out->push_back(line);
		}
		compressedFile=out;
		*file=backup;
		ReadAndWrite::writeFile(out,fileName);
	}
}

void GEAH_Compressor::extract(std::string fileName)
{
	if(file!=nullptr)
	{
		std::vector<std::string> backup = *file;
		auto* out = new std::vector<std::string>;
		for(int i=0;i<file->size();i++)
		{
			std::string line = file->at(i);
			bool bMadeReplacement=false;
			// I would like to apologize again for the next 268 lines. I'm truly sorry. I was tired and I really should've
			// parsed a config file, but here we are :)
			// refer to geahMapping.txt
			// there are many occurrences of 'green eggs and ham' being followed by 'I do not like them' on the next line
			if(line.find('1')!=std::string::npos)
			{
				findAndReplace(line,"1","green eggs and ham");
				findAndReplace(file->at(i+1),"","I do not like them");
				bMadeReplacement=true;
			}
			if(line.find('2')!=std::string::npos)
			{
				findAndReplace(line,"2","I do not like them");
				bMadeReplacement=true;
			}
			if(line.find('6')!=std::string::npos)
			{
				findAndReplace(line,"6","Would you like them");
				bMadeReplacement=true;
			}
			if(line.find('%')!=std::string::npos)
			{
				findAndReplace(line,"%","I would not could not");
				bMadeReplacement=true;
			}
			if(line.find('$')!=std::string::npos)
			{
				findAndReplace(line,"$","I will not eat them");
				bMadeReplacement=true;
			}
			if(line.find('=')!=std::string::npos)
			{
				findAndReplace(line,"=","And I will eat");
				bMadeReplacement=true;
			}
			if(line.find('+')!=std::string::npos)
			{
				findAndReplace(line,"+","And I would eat");
				bMadeReplacement=true;
			}
			if(line.find('`')!=std::string::npos)
			{
				findAndReplace(line,"`","I do not like");
				bMadeReplacement=true;
			}
			if(line.find('*')!=std::string::npos)
			{
				findAndReplace(line,"*","green eggs and ham");
				bMadeReplacement=true;
			}
			if(line.find("Ú")!=std::string::npos)
			{
				findAndReplace(line,"Ú","in the dark");
				bMadeReplacement=true;
			}
			if(line.find("§")!=std::string::npos)
			{
				findAndReplace(line,"§","in the rain");
				bMadeReplacement=true;
			}
			if(line.find('?')!=std::string::npos)
			{
				findAndReplace(line,"?","let me be");
				bMadeReplacement=true;
			}
			if(line.find('4')!=std::string::npos)
			{
				findAndReplace(line,"4","them Sam-I-am");
				bMadeReplacement=true;
			}
			if(line.find('7')!=std::string::npos)
			{
				findAndReplace(line,"7","Would you");
				bMadeReplacement=true;
			}
			if(line.find('8')!=std::string::npos)
			{
				findAndReplace(line,"8","Could you");
				bMadeReplacement=true;
			}
			if(line.find('9')!=std::string::npos)
			{
				findAndReplace(line,"9","would you");
				bMadeReplacement=true;
			}
			if(line.find('0')!=std::string::npos)
			{
				findAndReplace(line,"0","could you");
				bMadeReplacement=true;
			}
			if(line.find(']')!=std::string::npos)
			{
				findAndReplace(line,"]","You may");
				bMadeReplacement=true;
			}
			if(line.find('{')!=std::string::npos)
			{
				findAndReplace(line,"{","you may");
				bMadeReplacement=true;
			}
			if(line.find('^')!=std::string::npos)
			{
				findAndReplace(line,"^","A train");
				bMadeReplacement=true;
			}
			if(line.find('&')!=std::string::npos)
			{
				findAndReplace(line,"&","a train");
				bMadeReplacement=true;
			}
			if(line.find('~')!=std::string::npos)
			{
				findAndReplace(line,"~","in a");
				bMadeReplacement=true;
			}
			if(line.find('!')!=std::string::npos)
			{
				findAndReplace(line,"!","with a");
				bMadeReplacement=true;
			}
			if(line.find('5')!=std::string::npos)
			{
				findAndReplace(line,"5","like them");
				bMadeReplacement=true;
			}
			if(line.find("▓")!=std::string::npos)
			{
				findAndReplace(line,"▓","Thank you");
				bMadeReplacement=true;
			}
			if(line.find("®")!=std::string::npos)
			{
				findAndReplace(line,"®","green eggs");
				bMadeReplacement=true;
			}
			if(line.find("♣")!=std::string::npos)
			{
				findAndReplace(line,"♣","I like");
				bMadeReplacement=true;
			}
			if(line.find("Ä")!=std::string::npos)
			{
				findAndReplace(line,"Ä","I would");
				bMadeReplacement=true;
			}
			if(line.find("○")!=std::string::npos)
			{
				findAndReplace(line,"○","so good");
				bMadeReplacement=true;
			}
			if(line.find('3')!=std::string::npos)
			{
				findAndReplace(line,"3","them");
				bMadeReplacement=true;
			}
			if(line.find('(')!=std::string::npos)
			{
				findAndReplace(line,"(","fox");
				bMadeReplacement=true;
			}
			if(line.find(')')!=std::string::npos)
			{
				findAndReplace(line,")","box");
				bMadeReplacement=true;
			}
			if(line.find("ô")!=std::string::npos)
			{
				findAndReplace(line,"ô","Eat");
				bMadeReplacement=true;
			}
			if(line.find("ó")!=std::string::npos)
			{
				findAndReplace(line,"ó","Try");
				bMadeReplacement=true;
			}
			if(line.find('@')!=std::string::npos)
			{
				findAndReplace(line,"@","not");
				bMadeReplacement=true;
			}
			if(line.find('_')!=std::string::npos)
			{
				findAndReplace(line,"_","Not");
				bMadeReplacement=true;
			}
			if(line.find("£")!=std::string::npos)
			{
				findAndReplace(line,"£","Sam-I-am");
				bMadeReplacement=true;
			}
			if(line.find("ƒ")!=std::string::npos)
			{
				findAndReplace(line,"ƒ","mouse");
				bMadeReplacement=true;
			}
			if(line.find("ª")!=std::string::npos)
			{
				findAndReplace(line,"ª","house");
				bMadeReplacement=true;
			}
			if(line.find('.')!=std::string::npos)
			{
				findAndReplace(line,".","eat");
				bMadeReplacement=true;
			}
			if(line.find('>')!=std::string::npos)
			{
				findAndReplace(line,">","anywhere");
				bMadeReplacement=true;
			}
			if(line.find('<')!=std::string::npos)
			{
				findAndReplace(line,"<","here");
				bMadeReplacement=true;
			}
			if(line.find('/')!=std::string::npos)
			{
				findAndReplace(line,"/","there");
				bMadeReplacement=true;
			}
			if(line.find('\\')!=std::string::npos)
			{
				findAndReplace(line,"\\","would");
				bMadeReplacement=true;
			}
			if(line.find('|')!=std::string::npos)
			{
				findAndReplace(line,"|","could");
				bMadeReplacement=true;
			}
			if(line.find(';')!=std::string::npos)
			{
				findAndReplace(line,";","goat");
				bMadeReplacement=true;
			}
			if(line.find(':')!=std::string::npos)
			{
				findAndReplace(line,":","boat");
				bMadeReplacement=true;
			}
			if(line.find('\"')!=std::string::npos)
			{
				findAndReplace(line,"\"","Sam");
				bMadeReplacement=true;
			}
			if(line.find('\'')!=std::string::npos)
			{
				findAndReplace(line,"\'","car");
				bMadeReplacement=true;
			}
			if(line.find('[')!=std::string::npos)
			{
				findAndReplace(line,"[","tree");
				bMadeReplacement=true;
			}
			if(line.find("◘")!=std::string::npos)
			{
				findAndReplace(line,"◘","You");
				bMadeReplacement=true;
			}
			if(line.find("•")!=std::string::npos)
			{
				findAndReplace(line,"•","you");
				bMadeReplacement=true;
			}
			if(line.find("╚")!=std::string::npos)
			{
				findAndReplace(line,"╚","will");
				bMadeReplacement=true;
			}
			if(line.find("Ì")!=std::string::npos)
			{
				findAndReplace(line,"Ì","that");
				bMadeReplacement=true;
			}
			if(line.find("▀")!=std::string::npos)
			{
				findAndReplace(line,"▀","That");
				bMadeReplacement=true;
			}
			if(line.find("┌")!=std::string::npos)
			{
				findAndReplace(line,"┌","say");
				bMadeReplacement=true;
			}
			if(line.find("î")!=std::string::npos)
			{
				findAndReplace(line,"î","like");
				bMadeReplacement=true;
			}
			if(line.find("├")!=std::string::npos)
			{
				findAndReplace(line,"├","and");
				bMadeReplacement=true;
			}
			if(line.find("¨")!=std::string::npos)
			{
				findAndReplace(line,"¨","And");
				bMadeReplacement=true;
			}
			if(line.find("▄")!=std::string::npos)
			{
				findAndReplace(line,"▄","see");
				bMadeReplacement=true;
			}
			if(bMadeReplacement)
			{
				file->at(i)=line;
				i--;
			}
			else out->push_back(line);
		}
		out->push_back("");
		compressedFile=out;
		*file=backup;
		ReadAndWrite::writeFile(out,fileName);
	}
}
