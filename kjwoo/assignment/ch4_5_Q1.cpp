// //  문제 1

// 사실 위 erase 함수에는 한 가지 버그 있습니다. 
// 바로 사용자가 실수로 문자열의 실제 길이 보다 더 많이 지울 때 인데요, 
// 이 문제는 한 번 고쳐보세요. 이 버그는 김민성 님이 댓글로 제보 해주셨습니다 :) (난이도 : 하)

MyString& MyString::erase(int loc, int num)
 {
     // loc 의 앞 부터 시작해서 num 문자를 지운다.
     if (num < 0 || loc < 0 || loc > string_length) //인자가 잘못된경우 변경하지 않는다.
         return *this;

     if (num + loc > string_length) num = string_length - loc; //  범위를 문자열길이보다 길지 못하게 제한.
     
     for (int i = loc + num; i < string_length; i++) //뒷부분을 앞으로 가져와 삭제
     {
         string_content[i - num] = string_content[i];
     }

    string_length -= num;
    return *this;
 }
