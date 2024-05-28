#include <iostream>
#include <regex>
#include <vector>

void match_string() {
    // 주어진 파일 이름들.
    std::vector<std::string> file_names = {"db-123-log.txt", "db-124-log.txt", "not-db-log.txt", "db-12-log.txt",
                                           "db-12-log.jpg"};
    // \d*는 임의의 숫자를 의미한다.
    std::regex re("db-\\d*-log\\.txt");
    for (const auto& file_name : file_names) {
        // std::boolalpha 는 bool 을 0 과 1 대신에 false, true 로 표현하게 해줍니다.
        std::cout << file_name << ": " << std::boolalpha << std::regex_match(file_name, re) << '\n';
    }
}

void phone_nums() {
    std::vector<std::string> phone_numbers = {"010-1234-5678",  "010-123-4567",  "011-1234-5567",
                                              "010-12345-6789", "123-4567-8901", "010-1234-567"};

    // [01]은 0또는 1이라는 뜻이고 {}안에 있는 숫자는 해당 종류의 문자가 몇번 나타날 수있는지 나타내는 표현식이다.
    // 특정부분을 추출하고 싶다면 ()을 쳐줘서 추출하면된다.
    std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
    std::smatch match;  // 매칭된 결과를 string 으로 보관
    for (const auto& number : phone_numbers) {
        if (std::regex_match(number, match, re)) {
            for (size_t i = 0; i < match.size(); i++) {
                std::cout << "Match : " << match[i].str() << std::endl;
            }
            std::cout << "-----------------------\n";
        }
    }
}

void html_search() {
    std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
    std::smatch match;

    auto start = std::sregex_iterator(html.begin(), html.end(), re);
    auto end = std::sregex_iterator();

    while (start != end) {
        std::cout << start->str() << std::endl;
        ++start;
    }
}

void html_replace() {
    std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

    std::regex re(R"r(sk-circle(\d))r");
    std::smatch match;

    std::string modified_html = std::regex_replace(html, re, "$1-sk-circle");
    std::cout << modified_html;
}

int main() {
    match_string();
    phone_nums();
    html_search();
    html_replace();
}