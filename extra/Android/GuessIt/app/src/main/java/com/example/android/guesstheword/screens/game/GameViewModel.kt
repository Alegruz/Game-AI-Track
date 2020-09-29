package com.example.android.guesstheword.screens.game

import android.os.CountDownTimer
import android.text.format.DateUtils
import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Transformations
import androidx.lifecycle.ViewModel

private val CORRECT_BUZZ_PATTERN = longArrayOf(100, 100, 100, 100, 100, 100)
private val PANIC_BUZZ_PATTERN = longArrayOf(0, 200)
private val GAME_OVER_BUZZ_PATTERN = longArrayOf(0, 2000)
private val NO_BUZZ_PATTERN = longArrayOf(0)

class GameViewModel : ViewModel() {
    enum class BuzzType(val pattern: LongArray) {
        CORRECT(CORRECT_BUZZ_PATTERN),
        GAME_OVER(GAME_OVER_BUZZ_PATTERN),
        COUNTDOWN_PANIC(PANIC_BUZZ_PATTERN),
        NO_BUZZ(NO_BUZZ_PATTERN)
    }

    companion object {
        // These represent different important times
        // This is when the game is over
        const val DONE = 0L

        // This is the time when the phone will start buzzing each second
        private const val COUNTDOWN_PANIC_SECONDS = 10L

        // This is the number of milliseconds in a second
        const val ONE_SECOND = 1000L

        // This is the total time of the game
        const val COUNTDOWN_TIME = ONE_SECOND * 15
    }

    private val timer: CountDownTimer

    // The current timer
    private val mCurrentTime = MutableLiveData<Long>()
    private val currentTime: LiveData<Long>
        get() = mCurrentTime

    val currentTimeString = Transformations.map(currentTime) { time ->
        DateUtils.formatElapsedTime(time)
    }

    // The current word
    private val mWord = MutableLiveData<String>()
    val word: LiveData<String>
        get() = mWord

    // The current score
    private val mScore = MutableLiveData<Int>()
    val score: LiveData<Int>
        get() = mScore

    // The list of words - the front of the list is the next word to guess
    private lateinit var wordList: MutableList<String>

    private val mEventGameFinish = MutableLiveData<Boolean>()
    val eventGameFinish: LiveData<Boolean>
        get() = mEventGameFinish

    private val mEventBuzz = MutableLiveData<BuzzType>()
    val eventBuzz: LiveData<BuzzType>
        get() = mEventBuzz

    init {
        Log.i("GameViewModel", "GameViewModel created!")
        mEventGameFinish.value = false
        resetList()
        nextWord()
        mScore.value = 0
        mCurrentTime.value = COUNTDOWN_TIME / ONE_SECOND

        timer = object : CountDownTimer(COUNTDOWN_TIME, ONE_SECOND) {

            override fun onTick(millisUntilFinished: Long) {
                // TODO implement what should happen each tick of the timer
                mCurrentTime.value = (millisUntilFinished / ONE_SECOND)
                if (millisUntilFinished / ONE_SECOND <= COUNTDOWN_PANIC_SECONDS) {
                    mEventBuzz.value = BuzzType.COUNTDOWN_PANIC
                }
            }

            override fun onFinish() {
                // TODO implement what should happen when the timer finishes
                mCurrentTime.value = DONE
                mEventBuzz.value = BuzzType.GAME_OVER
                mEventGameFinish.value = true
            }
        }

        timer.start()
    }

    /**
     * Resets the list of words and randomizes the order
     */
    private fun resetList() {
        wordList = mutableListOf(
                "queen",
                "hospital",
                "basketball",
                "cat",
                "change",
                "snail",
                "soup",
                "calendar",
                "sad",
                "desk",
                "guitar",
                "home",
                "railway",
                "zebra",
                "jelly",
                "car",
                "crow",
                "trade",
                "bag",
                "roll",
                "bubble"
        )
        wordList.shuffle()
    }

    /**
     * Moves to the next word in the list
     */
    private fun nextWord() {
        // Select and remove a word from the list
        if (wordList.isEmpty()) {
            // gameFinished()
            resetList()
            mEventGameFinish.value = true
        }

        mWord.value = wordList.removeAt(0)
    }

    /** Methods for buttons presses **/

    fun onSkip() {
        mScore.value = if (mScore.value!! > 0) (mScore.value)?.minus(1) else 0
        nextWord()
    }

    fun onCorrect() {
        mScore.value = (mScore.value)?.plus(1)
        mEventBuzz.value = BuzzType.CORRECT
        nextWord()
    }


    override fun onCleared() {
        super.onCleared()
        Log.i("GameViewModel", "GameViewModel destroyed!")
    }

    fun onGameFinishComplete() {
        mEventGameFinish.value = false
    }

    fun onBuzzComplete() {
        mEventBuzz.value = BuzzType.NO_BUZZ
    }
}