class Score {
public:
    Score(int x) : score(new int(x)) {}

    Score(const Score& source) : score(new int(*source.score)) {}

    Score(Score&& source) {
        score = source.score;
        source.score = nullptr;
    }

    Score &operator=(const Score& source) {
        if (this == &source) return *this;
        if (!score) { score = new int(); }
        *score = *source.score;
        return *this;
    }

    Score &operator=(Score &&source) {
        if (this == &source) return *this;
        if (score) delete score;
        score = source.score;
        source.score = nullptr;
        return *this;
    }

    ~Score() {
        if (score) delete score;
    }

    bool operator==(const int &number) const {
        return *score == number;
    }

    void Increase() {
        Increase(1);
    }

    void Increase(int s) {
        *score += s;
    }

    int Get() const {
        if (score) {
            return *score;
        } else {
            return 0;
        }
    }

private:
    int *score;
};